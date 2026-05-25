#include "MarkVehicleReadyForPickupUsecase.h"

#include <memory>

MarkVehicleReadyForPickupUsecase::MarkVehicleReadyForPickupUsecase(VehicleRepository &repository) : vehicleRepository_(repository) {}

void MarkVehicleReadyForPickupUsecase::execute(const std::string_view licensePlate) const {
    vehicleRepository_.findByRegistration(licensePlate) -> markReadyForPickup();
}