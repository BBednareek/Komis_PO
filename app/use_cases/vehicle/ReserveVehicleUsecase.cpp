#include "ReserveVehicleUsecase.h"

#include <memory>

#include "../../../domain/common/Exceptions.h"

ReserveVehicleUsecase::ReserveVehicleUsecase(VehicleRepository& repository) : repository_(repository) {}

void ReserveVehicleUsecase::execute(const std::string_view licensePlate) const {
    const auto vehicle = repository_.findByRegistration(licensePlate);

    if (vehicle == nullptr) throw VehicleException("Nie znaleziono pojazdu w bazie");

    vehicle -> reserve();
}
