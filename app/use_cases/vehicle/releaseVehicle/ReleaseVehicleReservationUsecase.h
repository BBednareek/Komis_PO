#ifndef KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
#define KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
#include "../../../../domain/account/EmployeeAccount.h"
#include "../../../../domain/repositories/VehicleRepository.h"

class ReleaseVehicleReservationUsecase final {
public:
    explicit ReleaseVehicleReservationUsecase(VehicleRepository& repository);

    void execute(EmployeeAccount& employee, std::string_view licensePlate) const;

private:
    VehicleRepository& repository_;
};


#endif //KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
