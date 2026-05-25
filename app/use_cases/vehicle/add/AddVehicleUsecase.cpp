#include "AddVehicleUsecase.h"
#include "../../../../domain/common/Exceptions.h"

AddVehicleUsecase::AddVehicleUsecase(VehicleRepository& repository) : vehicleRepository_(repository) {}

void AddVehicleUsecase::execute(std::shared_ptr<Vehicle> vehicle) const {
    if (vehicle == nullptr) throw ValidationException("Nie mozna dodac pustego poijazdu");

    vehicleRepository_.add(std::move(vehicle));
}