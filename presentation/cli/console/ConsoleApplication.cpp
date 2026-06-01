#include "ConsoleApplication.h"

#include <iostream>

#include "../../../domain/common/Exceptions.h"

namespace {
    const char* toString(const FuelType fuelType) {
        switch (fuelType) {
            case FuelType::Petrol: return "benzyna";
            case FuelType::Diesel: return "diesel";
            case FuelType::Hybrid: return "hybryda";
            case FuelType::Electric: return "elektryczny";
            case FuelType::LPG: return "lpg";
        }

        return "nieznany";
    }

    const char* toString(const VehicleStatus status) {
        switch (status) {
            case VehicleStatus::Reserved: return "zarezerwowany";
            case VehicleStatus::ReadyForPickup: return "gotowy do odbioru";
            case VehicleStatus::ForSale: return "na sprzedaz";
        }
        return "nieznany";
    }

    FuelType toFuelType(const std::string& rawValue) {
        if (rawValue == "1") return FuelType::Petrol;
        if (rawValue == "2") return FuelType::Diesel;
        if (rawValue == "3") return FuelType::Hybrid;
        if (rawValue == "4") return FuelType::Electric;
        if (rawValue == "5") return FuelType::LPG;

        throw std::invalid_argument("Niepoprawny typ paliwa");
    }
}

ConsoleApplication::ConsoleApplication(System& system) :
        system_(system),
        customerLoginUseCase_(system.accounts()),
        searchVehicleUseCase_(system.vehicles()),
        employeeLoginUseCase_(system.accounts()),
        completeTaskUseCase_(system.tasks()),
        addVehicleUseCase_(system.vehicles()),
        removeVehicleUseCase_(system.vehicles()),
        markVehicleReadyForPickupUseCase_(system.vehicles()),
        releaseVehicleReservationUseCase_(system.vehicles()),
        reserveVehicleUseCase_(system.vehicles(),
                               system.accounts(),
                               system.tasks()) {}

void ConsoleApplication::run() const {
    bool running = true;

    while (running) {
        try {
            const MainAction action = Menu::promptMainAction();
            if (action == MainAction::Exit) {
                running = false;
                continue;
            }

            handleMainAction(action);
        } catch (const std::exception& e) {
            printMessage(e.what());
        }
    }

    printMessage("Do zobaczenia");
}

void ConsoleApplication::handleMainAction(const MainAction action) const {
    switch (action) {
        case MainAction::CustomerLogin:
            handleCustomerLogin();
            break;

        case MainAction::EmployeeLogin:
            handleEmployeeLogin();
            break;

        case MainAction::ShowVehicles:
            showVehicles();
            break;
        case MainAction::Exit:
            break;
        default:
            printMessage("Nieznana opcja menu");
            break;
    }
}
void ConsoleApplication::handleCustomerLogin() const {
    const auto login = Menu::prompt("Login klienta: ");
    const auto password = Menu::prompt("Haslo: ");
    const auto account = customerLoginUseCase_.execute(login, password);

    printMessage("Logowanie klienta zakonczone sukcesem");
    customerPanel(account);
}
void ConsoleApplication::handleEmployeeLogin() const {
    const auto login = Menu::prompt("Login Pracownika: ");
    const auto password = Menu::prompt("Haslo: ");
    const auto account = employeeLoginUseCase_.execute(login, password);

    printMessage("Logowanie pracownika zakonczone sukcesem");
    employeePanel(account);
}
void ConsoleApplication::customerPanel(const std::shared_ptr<Account>& account) const {
    const auto& customer = requireCustomerAccount(account);
    bool loggedIn = true;

    while (loggedIn) {
        try {
            switch (Menu::promptCustomerAction()) {
                case CustomerAction::ShowVehicles:
                    showVehicles();
                    break;
                case CustomerAction::ReserveVehicle:
                    reserveVehicleFlow(customer);
                    break;
                case CustomerAction::SearchVehicle:
                    searchVehicles();
                    break;
                case CustomerAction::CollectVehicle:
                    //TODO
                    break;

                case CustomerAction::ShowData:
                    break;

                case CustomerAction::ChangeAddress:
                    break;

                case CustomerAction::Logout:
                    account -> logout();
                    loggedIn = false;
                    printMessage("Wylogowano klienta");
                    break;
                default:
                    printMessage("Nieznana opcja menu klienta");
                    break;
            }
        } catch (const std::exception& e) { printMessage(e.what()); }
    }
}
void ConsoleApplication::employeePanel(const std::shared_ptr<Account>& account) const {
    auto& employee = requireEmployeeAccount(account);
    bool loggedIn = true;

    while (loggedIn) {
        try {
            switch (Menu::promptEmployeeAction()) {
                case EmployeeAction::ShowVehicles:
                    showVehicles();
                    break;
                case EmployeeAction::AddVehicle:
                    addVehicleFlow();
                    break;
                case EmployeeAction::RemoveVehicle:
                    removeVehicleFlow();
                    break;
                case EmployeeAction::MarkReadyForPickup:
                    markReadyForPickupFlow();
                    break;
                case EmployeeAction::ReleaseReservation:
                    releaseReservationFlow(employee);
                    break;
                case EmployeeAction::ShowTasks:
                    showEmployeeTasks(employee);
                    break;
                case EmployeeAction::CompleteTask:
                    completeEmployeeTaskFlow(employee);
                    break;
                case EmployeeAction::Logout:
                    account -> logout();
                    loggedIn = false;
                    printMessage("Wylogowano pracownika");
                    break;
                default:
                    printMessage("Nieznana opcja menu pracownika");
                    break;
            }
        } catch (const std::exception& e) { printMessage(e.what()); }
    }
}
void ConsoleApplication::showVehicles() const {
    const auto vehicles = system_.vehicles().getAllVehicles();

    if (vehicles.empty()) {
        printMessage("Brak pojazdow w bazie");
        return;
    }

    std::cout << "\n=== LISTA POJAZDOW ===\n";
    for (const auto& vehicle : vehicles) {
        std::cout << vehicle.displayName()
        << " | numer rejestracyjny: " << vehicle.licensePlate
        << " | moc: " << vehicle.horsePower << " KM"
        << " | rok: " << vehicle.productionYear
        << " | pojemnosc skokowa: " << vehicle.engineCapacity
        << " | paliwo: " << toString(vehicle.fuelType)
        << " | data waznosci badania okresowego: " << vehicle.expirationDate
        << " | status: " << toString(vehicle.vehicleStatus)
        << '\n';
    }
}
void ConsoleApplication::reserveVehicleFlow(const CustomerAccount& customer) const {
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu: ");
    reserveVehicleUseCase_.execute(customer, licensePlate);
    printMessage("Pojazd zostal zarezerwowany i przekazany do obslugi pracownika");
}

void ConsoleApplication::addVehicleFlow() const {
    const auto brand = Menu::prompt("Marka: ");
    const auto model = Menu::prompt("Model: ");
    const auto licensePlate = Menu::prompt("Numer rejestracyjny: ");
    const auto horsePower = readUnsigned("Moc (KM): ");
    const auto productionDate = readUnsigned("Rok produkcji: ");
    const auto expirationDate = Menu::prompt("Data waznosci przegladu (YYYY-MM-DD): ");
    const auto engineCapacity = readDouble("Pojemnosc silnika: ");

    std::cout << "Typ paliwa:\n"
    << "1. Benzyna\n"
    << "2. Diesel\n"
    << "3. Hybryda\n"
    << "4. Elektryczny\n"
    << "5. LPG\n";
    const auto fuelType = toFuelType(Menu::prompt("Wybor: "));

    const auto vehicle = std::make_shared<Vehicle>(
    brand,
    model,
    licensePlate,
    horsePower,
    productionDate,
    expirationDate,
    engineCapacity,
    fuelType
    );

    addVehicleUseCase_.execute(vehicle);
    printMessage("Pojazd zostal dodany");

}
void ConsoleApplication::removeVehicleFlow() const {
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu do usuniecia: ");
    removeVehicleUseCase_.execute(licensePlate);
    printMessage("Operacja usuniecia zostala wykonana");
}
void ConsoleApplication::markReadyForPickupFlow() const {
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu do oznaczenia jako gotowy do odbioru: ");
    markVehicleReadyForPickupUseCase_.execute(licensePlate);
    printMessage("Pojazd oznaczono jako gotowy do odbioru");
}

void ConsoleApplication::releaseReservationFlow(const EmployeeAccount& employee) const {
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu do usuniecia: ");
    releaseVehicleReservationUseCase_.execute(licensePlate);

    for (const auto& task : employee.getTaskList())
        if (task->getAssignedVehicle().lock()->getLicensePlate() == licensePlate) task->complete();


    printMessage("Rezerwacja pojazdu zostala zwolniona");
}
void ConsoleApplication::showEmployeeTasks(const EmployeeAccount& employee) {
    const auto& tasks = employee.getTaskList();

    if (tasks.empty()) {
        printMessage("Brak zadan dla pracownika");
        return;
    }

    std::cout << "\n=== LISTA ZADAN: " << employee.getFullName() << " ===\n";
    for (std::size_t index = 0; index < tasks.size(); ++index) {
        if (const auto& task = tasks[index])
            std::cout << index + 1 << ". " << *task << '\n';
    }
}

void ConsoleApplication::searchVehicles() const {
    VehicleSearchCriteria vehicleSearchCriteria {};
    std::string customerInput;

    std::cout << "\n=== WYSZUKIWANIE POJAZDU ===\n";
    std::cout << "Wartosci sa opcjonalne\n";
    std::cout << "W celu pominiecia wpisywania wcisnij Enter\n";

    std::cout << "Marka: ";
    if (std::getline(std::cin, customerInput) && !customerInput.empty())
        vehicleSearchCriteria.brand.emplace(std::move(customerInput));

    std::cout << "Model: ";
    if (std::getline(std::cin, customerInput) && !customerInput.empty())
        vehicleSearchCriteria.model.emplace(std::move(customerInput));

    std::cout << "Minimalny rok produkcji: ";
    if (std::getline(std::cin, customerInput) && !customerInput.empty())
        vehicleSearchCriteria.minYear.emplace(static_cast<std::uint32_t>(std::stoul(customerInput)));

    std::cout << "Maksymalny rok produkcji: ";
    if (std::getline(std::cin, customerInput) && !customerInput.empty())
        vehicleSearchCriteria.maxYear.emplace(static_cast<std::uint32_t>(std::stoul(customerInput)));

    std::cout << "Pojemnosc silnika: ";
    if (std::getline(std::cin, customerInput) && !customerInput.empty())
        vehicleSearchCriteria.engineCapacity.emplace(std::stod(customerInput));

    const std::vector<VehicleData> result = searchVehicleUseCase_.execute(vehicleSearchCriteria);

    if (result.empty()) {
        std::cout << "Brak pojazdow w sprzedazy, ktore spelniaja zadane warunki";
        return;
    }

    std::cout << "\n=== LISTA POJAZDOW ===\n";
    for (const auto& vehicle : result) {
        std::cout << vehicle.displayName()
        << " | numer rejestracyjny: " << vehicle.licensePlate
        << " | moc: " << vehicle.horsePower << " KM"
        << " | rok: " << vehicle.productionYear
        << " | pojemnosc skokowa: " << vehicle.engineCapacity
        << " | paliwo: " << toString(vehicle.fuelType)
        << " | data waznosci badania okresowego: " << vehicle.expirationDate
        << " | status: " << toString(vehicle.vehicleStatus)
        << '\n';

    }
}

void ConsoleApplication::completeEmployeeTaskFlow(EmployeeAccount& employee) const {
    showEmployeeTasks(employee);

    const auto taskIndex = readUnsigned("Podaj numer zadania do zakonczenia: ");
    if (taskIndex <= 0) throw TaskException("Numer zadania musi byc wiekszy od zera");

    completeTaskUseCase_.execute(employee, taskIndex - 1);
    printMessage("Zadanie zostalo oznaczone jako zakonczone");
}

void ConsoleApplication::printMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

[[nodiscard]] CustomerAccount& ConsoleApplication::requireCustomerAccount(const std::shared_ptr<Account>& account) {
    const auto customer = std::dynamic_pointer_cast<CustomerAccount>(account);
    if (customer == nullptr) throw AuthenticationException("Zalogowane konto nie jest kontem klienta");

    return *customer;
}

[[nodiscard]] EmployeeAccount& ConsoleApplication::requireEmployeeAccount(const std::shared_ptr<Account>& account) {
    const auto customer = std::dynamic_pointer_cast<EmployeeAccount>(account);
    if (customer == nullptr) throw AuthenticationException("Zalogowane konto nie jest kontem pracownika");

    return *customer;
}

[[nodiscard]] double ConsoleApplication::readDouble(const std::string& label) {
    const auto value = Menu::prompt(label);
    return std::stod(value);
}

[[nodiscard]] std::uint32_t ConsoleApplication::readUnsigned(const std::string& label) {
    const auto value = Menu::prompt(label);
    return static_cast<std::uint32_t>(std::stoul(value));
}