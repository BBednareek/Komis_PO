#include "ConsoleApplication.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "../../../domain/common/Exceptions.h"
#include "../../../domain/task/Task.h"

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

    const char* toString(const TaskStatus status) {
        switch (status) {
            case TaskStatus::Pending: return "oczekujace";
            case TaskStatus::ReadyForPickup: return "gotowe do odbioru";
            case TaskStatus::Completed: return "wykonane";
            case TaskStatus::Cancelled: return "anulowane";
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

    void printVehicle(const VehicleData& vehicle) {
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

    void printTask(const Task& task) {
        std::cout << task.getTaskName()
        << " | "
        << task.getTaskDescription()
        << " | status: "
        << toString(task.getTaskStatus());

        std::cout << " | pojazd: " << task.getAssignedVehicleLicensePlate();
        if (!task.getAssignedCustomerName().empty()) {
            std::cout << " | kupujacy: " << task.getAssignedCustomerName();
        }

        std::cout << '\n';
    }
}

ConsoleApplication::ConsoleApplication(System& system) :
        system_(system),
        customerLoginUseCase_(system.accounts()),
        searchVehicleUseCase_(system.vehicles()),
        employeeLoginUseCase_(system.accounts()),
        addVehicleUseCase_(system.vehicles()),
        removeVehicleUseCase_(system.vehicles()),
        markVehicleReadyForPickupUseCase_(system.vehicles(), system.tasks()),
        releaseVehicleReservationUseCase_(system.vehicles()),
        reserveVehicleUseCase_(system.vehicles(),
                               system.accounts(),
                               system.tasks()),
        collectVehicleUseCase_(system.vehicles(), system.tasks()) {}

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
    const auto customer = requireCustomerAccount(account);
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
                    if (!canCollectVehicle(*customer)) {
                        printMessage("Nie masz aktualnie zadnego pojazdu gotowego do odbioru");
                        break;
                    }
                    collectVehicleFlow(customer);
                    break;
                case CustomerAction::ShowData:
                    showCustomerData(*customer);
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
                    markReadyForPickupFlow(employee);
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
                case EmployeeAction::ShowEmployeeData:
                    showEmployeeData(employee);
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
        printVehicle(vehicle);
    }
}
void ConsoleApplication::showCustomerData(const CustomerAccount& customer) const {
    std::cout << "\n=== DANE KLIENTA ===\n";
    std::cout << "Imie i nazwisko: " << customer.getFullName() << '\n';
    std::cout << "Adres: " << customer.getAddress() << '\n';
}

void ConsoleApplication::showEmployeeData(const EmployeeAccount& employee) const {
    std::cout << "\n=== DANE PRACOWNIKA ===\n";
    std::cout << "Imie i nazwisko: " << employee.getFullName() << '\n';
}

void ConsoleApplication::reserveVehicleFlow(const std::shared_ptr<CustomerAccount>& customer) const {
    showVehicles();
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu: ");
    reserveVehicleUseCase_.execute(customer, licensePlate);
    printMessage("Pojazd zostal zarezerwowany i przekazany do obslugi pracownika");
}

void ConsoleApplication::collectVehicleFlow(const std::shared_ptr<CustomerAccount>& customer) const {
    const auto vehicles = customer -> getReservedVehicleList();
    bool found = false;

    for (const auto& vehicle : vehicles) {
        if (vehicle == nullptr) continue;

        if (vehicle -> getVehicleStatus() != VehicleStatus::ReadyForPickup) continue;

        found = true;

        const auto data = vehicle -> getVehicleData();

        printVehicle(data);
    }

    if (!found) {printMessage("Brak pojazdow gotowych do odbioru"); return;}

    const auto licensePlate = Menu::prompt("\nPodaj numer rejestracyjny pojazdu do odbioru: ");
    collectVehicleUseCase_.execute(customer, licensePlate);
    printMessage("Pojazd zostal odebrany przez kupujacego");
}

bool ConsoleApplication::canCollectVehicle(const CustomerAccount& customer) const {
    for (const auto& task : system_.tasks().getAllTasks()) {
        if (task == nullptr) continue;
        if (task->getTaskStatus() != TaskStatus::ReadyForPickup) continue;
        if (task->getAssignedCustomerName().empty()) continue;
        if (task->getAssignedCustomer().expired()) continue;

        const auto assignedCustomer = task->getAssignedCustomer().lock();
        if (assignedCustomer == nullptr) continue;
        if (assignedCustomer->getLogin() != customer.getLogin()) continue;

        return true;
    }

    return false;
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
void ConsoleApplication::markReadyForPickupFlow(const EmployeeAccount& employee) const {
    showEmployeeTasks(employee);
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu do oznaczenia jako gotowy do odbioru: ");
    markVehicleReadyForPickupUseCase_.execute(licensePlate);
    printMessage("Pojazd oznaczono jako gotowy do odbioru");
}

void ConsoleApplication::releaseReservationFlow(EmployeeAccount& employee) const {
    const auto licensePlate = Menu::prompt("Podaj numer rejestracyjny pojazdu do usuniecia: ");
    releaseVehicleReservationUseCase_.execute(employee, licensePlate);
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
        if (const auto& task = tasks[index]) {
            std::cout << index + 1 << ". ";
            printTask(*task);
        }
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

    const std::vector<VehicleData> result = searchVehicleUseCase_.execute(vehicleSearchCriteria);

    if (result.empty()) {
        std::cout << "Brak pojazdow w sprzedazy, ktore spelniaja zadane warunki";
        return;
    }

    std::cout << "\n=== LISTA POJAZDOW ===\n";
    for (const auto& vehicle : result) {
        printVehicle(vehicle);
    }
}

void ConsoleApplication::completeEmployeeTaskFlow(EmployeeAccount& employee) const    {
    showEmployeeTasks(employee);

    const auto taskIndex = readUnsigned("Podaj numer zadania do zakonczenia: ");
    if (taskIndex <= 0) throw TaskException("Numer zadania musi byc wiekszy od zera");

    completeTaskUseCase_.execute(employee, taskIndex - 1);
    printMessage("Zadanie zostalo oznaczone jako zakonczone");
}

void ConsoleApplication::printMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

[[nodiscard]] std::shared_ptr<CustomerAccount> ConsoleApplication::requireCustomerAccount(const std::shared_ptr<Account>& account) {
    const auto customer = std::dynamic_pointer_cast<CustomerAccount>(account);
    if (customer == nullptr) throw AuthenticationException("Zalogowane konto nie jest kontem klienta");

    return customer;
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
