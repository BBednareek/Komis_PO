#include "Task.h"
#include "TaskStatus.h"

Task::Task(
    std::string taskName,
    std::string description,
    const std::shared_ptr<Vehicle>& vehicle,
    const TaskStatus status) :
    taskName_(std::move(taskName)),
    taskDescription_(std::move(description)),
    vehicle_(vehicle),
    status_(status) {}
[[nodiscard]] const std::string& Task::getTaskName() const { return taskName_; }
[[nodiscard]] const std::string& Task::getTaskDescription() const { return taskDescription_; }
[[nodiscard]] const std::weak_ptr<Vehicle>& Task::getAssignedVehicle() const { return vehicle_; }
[[nodiscard]] const TaskStatus& Task::getTaskStatus() const { return status_; }
void Task::complete() { status_ = TaskStatus::Completed; }

TaskData Task::getTaskData() const {
    TaskData data {
        .taskName = taskName_,
        .description = taskDescription_,
        .assignedVehicleLicensePlate = "",
        .status = status_
    };
    if (const auto vehicle = vehicle_.lock()) data.assignedVehicleLicensePlate = vehicle->getLicensePlate();

    return data;
}
