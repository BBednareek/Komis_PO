#include "RemoveVehicleUsecase.h"

RemoveVehicleUsecase::RemoveVehicleUsecase(VehicleRepository& repository) : repository_(repository) {}

void RemoveVehicleUsecase::execute(const std::string_view licensePlate) const {
    repository_.remove(licensePlate);
}
