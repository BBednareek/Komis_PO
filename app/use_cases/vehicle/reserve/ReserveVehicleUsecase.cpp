#include "ReserveVehicleUsecase.h"
#include "../../../../domain/common/Exceptions.h"
#include <limits>
#include "../../../services/taskGenerator/TaskGenerator.h"

ReserveVehicleUsecase::ReserveVehicleUsecase(
    VehicleRepository&  vehicleRepository,
    AccountRepository&  accountRepository,
    TaskRepository&     taskRepository
    ) :
    vehicleRepository_(vehicleRepository),
    taskRepository_(taskRepository),
    accountRepository_(accountRepository) {}

void ReserveVehicleUsecase::execute(const CustomerAccount& customer, const std::string_view licensePlate) const {
    const auto employee = findAvailableEmployees();
    const auto vehicle  = vehicleRepository_.findByRegistration(licensePlate);

    vehicle -> reserve();

    const auto [name, description] =
    TaskGenerator::generateReservationTask(customer.getFullName());

    const auto task = std::make_shared<Task>(

        name,
        description,
        vehicle,
        TaskStatus::Pending
    );

    employee->assignTask(task);
    taskRepository_.add(task);
}

std::shared_ptr<EmployeeAccount> ReserveVehicleUsecase::findAvailableEmployees() const {
    const auto employees = accountRepository_.getAllEmployees();

    if (employees.empty()) throw TaskException("Brak pracownikow do obslugi rezerwacji");

    std::shared_ptr<EmployeeAccount> selectedEmployee = nullptr;
    auto lowestPendingTaskCount = std::numeric_limits<std::uint32_t>::max();

    for (const auto& employee : employees) {
        if (employee == nullptr) continue;

        if (const auto pendingTaskCount = employee->getPendingTaskCount(); selectedEmployee == nullptr || pendingTaskCount < lowestPendingTaskCount) {
            selectedEmployee = employee;
            lowestPendingTaskCount = pendingTaskCount;
        }
    }
    if (selectedEmployee == nullptr) throw TaskException("Nie znaleziono dostepnego pracownika");

    return selectedEmployee;
}