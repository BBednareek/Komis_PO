#include "ReleaseVehicleReservationUsecase.h"

#include <memory>

ReleaseVehicleReservationUsecase::ReleaseVehicleReservationUsecase(VehicleRepository& repository) : repository_(repository) {}

void ReleaseVehicleReservationUsecase::execute(EmployeeAccount& employee, const std::string_view licensePlate) const {
    repository_.findByRegistration(licensePlate) -> release();
    employee.completeTasksForVehicle(licensePlate);
}
