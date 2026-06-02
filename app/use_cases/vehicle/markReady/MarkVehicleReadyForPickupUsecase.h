#ifndef KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
#define KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
#include <string_view>
#include "../../../../domain/repositories/VehicleRepository.h"
#include "../../../../domain/repositories/TaskRepository.h"

class MarkVehicleReadyForPickupUsecase final {
public:
    explicit MarkVehicleReadyForPickupUsecase(VehicleRepository& repository, TaskRepository& taskRepository);

    void execute(std::string_view licensePlate) const;

private:
    VehicleRepository& vehicleRepository_;
    TaskRepository& taskRepository_;
};


#endif //KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
