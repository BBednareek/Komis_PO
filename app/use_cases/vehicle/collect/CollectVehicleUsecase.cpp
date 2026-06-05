#include "CollectVehicleUsecase.h"

#include "../../../../domain/task/Task.h"
#include "../../../../domain/common/Exceptions.h"

CollectVehicleUsecase::CollectVehicleUsecase(
    VehicleRepository& vehicleRepository,
    TaskRepository& taskRepository
) :
    vehicleRepository_(vehicleRepository),
    taskRepository_(taskRepository) {}

void CollectVehicleUsecase::execute(const std::shared_ptr<CustomerAccount>& customer, const std::string_view licensePlate) const {
    if (customer == nullptr) throw ValidationException("Nie mozna odebrac pojazdu bez zalogowanego kupujacego");

    if (const auto vehicle = vehicleRepository_.findByRegistration(licensePlate); vehicle->getVehicleStatus() != VehicleStatus::ReadyForPickup)
        throw VehicleException("Pojazd nie jest gotowy do odbioru");

    std::shared_ptr<Task> matchingTask = nullptr;

    for (const auto& task : taskRepository_.getAllTasks()) {
        if (task == nullptr) continue;
        if (task->getAssignedVehicleLicensePlate() != licensePlate) continue;
        if (task->getTaskStatus() != TaskStatus::ReadyForPickup) continue;

        const auto assignedCustomer = task->getAssignedCustomer().lock();
        if (assignedCustomer == nullptr) continue;
        if (assignedCustomer == customer) {
            matchingTask = task;
            break;
        }
    }

    if (matchingTask == nullptr) throw AuthenticationException("Tylko przypisany kupujacy moze odebrac ten pojazd");

    matchingTask->complete();

    customer->removeReservedVehicle(std::string{licensePlate});
    vehicleRepository_.remove(licensePlate);
    customer->incrementPurchasedVehicles();
}
