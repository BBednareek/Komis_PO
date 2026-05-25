#include <memory>

#include "../app/services/System.h"
#include "../infrastructure/repositories/account/AccountRepositoryImpl.h"
#include "../infrastructure/repositories/repository/VehicleRepositoryImpl.h"
#include "../infrastructure/repositories/task/TaskRepositoryImpl.h"
#include "../presentation/cli/console/ConsoleApplication.h"

namespace {
    void seedData(const System& system) {
        const auto customer = std::make_shared<CustomerAccount>("Jan", "Kowalski", "Warszawa", "jan", "1234");
        auto vehicleOne = std::make_shared<Vehicle>("BMW", "M3", "WX12345", 510, 2022, "2027-05-31", 3.0, FuelType::Petrol);
        const auto vehicleTwo = std::make_shared<Vehicle>("Toyota", "Corolla", "WS54231", 320, 2012, "2029-01-01", 1.4, FuelType::Hybrid);

        const auto task = std::make_shared<Task>(
            "Przygotuj pojazd", "Mycie i sprawdzenie dokumentow", vehicleOne, TaskStatus::Pending
        );

        const auto employeeone = std::make_shared<EmployeeAccount>(
            1, "Bartek", "Bednarek", "bartek", "bednarek", std::vector<std::shared_ptr<Task>>{task});
        const auto employeetwo = std::make_shared<EmployeeAccount>(
            2, "Michal", "Bednarek", "michal", "chuj", std::vector<std::shared_ptr<Task>>{});

        system.accounts().addCustomer(customer);
        system.accounts().addEmployee(employeeone);
        system.accounts().addEmployee(employeetwo);
        system.vehicles().add(vehicleOne);
        system.vehicles().add(vehicleTwo);
        system.tasks().add(task);
    }
}

int main() {
    auto accountRepository  = std::make_unique<AccountRepositoryImpl>();
    auto vehicleRepository  = std::make_unique<VehicleRepositoryImpl>();
    auto taskRepository     = std::make_unique<TaskRepositoryImpl>();

    System system(std::move(accountRepository), std::move(vehicleRepository), std::move(taskRepository));
    seedData(system);

    const ConsoleApplication app(system);
    app.run();
}
