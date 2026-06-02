#include "MarkVehicleReadyForPickupUsecase.h"

#include "../../../../domain/task/Task.h"
#include "../../../../domain/common/Exceptions.h"
#include <memory>

MarkVehicleReadyForPickupUsecase::MarkVehicleReadyForPickupUsecase(VehicleRepository &repository, TaskRepository& taskRepository) :
    vehicleRepository_(repository),
    taskRepository_(taskRepository) {}

void MarkVehicleReadyForPickupUsecase::execute(const std::string_view licensePlate) const {
    std::shared_ptr<Task> matchingTask = nullptr;
    for (const auto& task : taskRepository_.getAllTasks()) {
        if (task == nullptr) continue;
        if (task->getAssignedVehicleLicensePlate() != licensePlate) continue;
        if (task->getTaskStatus() != TaskStatus::Completed) continue;

        matchingTask = task;
        break;
    }

    if (matchingTask == nullptr) {
        throw TaskException("Nie znaleziono aktywnego zadania dla podanego pojazdu");
    }

    const auto vehicle = vehicleRepository_.findByRegistration(licensePlate);
    vehicle->markReadyForPickup();
    matchingTask->markReadyForPickup();
}
