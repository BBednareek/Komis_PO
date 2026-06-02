#include "Task.h"

#include "TaskStatus.h"
#include "../account/CustomerAccount.h"
#include "../vehicle/Vehicle.h"
#include "../common/Exceptions.h"

Task::Task(
    std::string taskName,
    std::string description,
    const std::shared_ptr<Vehicle>& vehicle,
    const std::shared_ptr<CustomerAccount>& customer,
    const TaskStatus status
) :
    taskName_(std::move(taskName)),
    taskDescription_(std::move(description)),
    vehicle_(vehicle),
    customer_(customer),
    assignedVehicleLicensePlate_(vehicle ? vehicle->getLicensePlate() : std::string{}),
    assignedCustomerName_(customer ? customer->getFullName() : std::string{}),
    status_(status) {}

[[nodiscard]] const std::string& Task::getTaskName() const { return taskName_; }
[[nodiscard]] const std::string& Task::getTaskDescription() const { return taskDescription_; }
[[nodiscard]] const std::weak_ptr<CustomerAccount>& Task::getAssignedCustomer() const { return customer_; }
[[nodiscard]] const std::string& Task::getAssignedVehicleLicensePlate() const { return assignedVehicleLicensePlate_; }
[[nodiscard]] const std::string& Task::getAssignedCustomerName() const { return assignedCustomerName_; }
[[nodiscard]] const TaskStatus& Task::getTaskStatus() const { return status_; }
[[nodiscard]] const std::weak_ptr<Vehicle>& Task::getVehicle() const noexcept { return vehicle_; }


void Task::markReadyForPickup() {
    status_ = TaskStatus::ReadyForPickup;
}

void Task::complete() {
    if (status_ == TaskStatus::Cancelled) throw TaskException("Anulowane zadanie nie moze zostac zakonczenie");
    status_ = TaskStatus::Completed;
}

void Task::cancel() {
    if (status_ == TaskStatus::Completed) throw TaskException("Zakonczone zadanie nie moze zostac anulowane");
    status_ = TaskStatus::Cancelled;
}

