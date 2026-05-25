#ifndef KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
#define KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
#include "../../../../domain/repositories/VehicleRepository.h"

class MarkVehicleReadyForPickupUsecase final {
public:
    explicit MarkVehicleReadyForPickupUsecase(VehicleRepository& repository);

    void execute(std::string_view licensePlate) const;

private:
    VehicleRepository& vehicleRepository_;
};


#endif //KOMISPO_MARKVEHICLEREADYFORPICKUPUSECASE_H
