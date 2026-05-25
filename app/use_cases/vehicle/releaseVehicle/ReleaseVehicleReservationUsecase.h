#ifndef KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
#define KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
#include "../../../../domain/repositories/VehicleRepository.h"

class ReleaseVehicleReservationUsecase final {
public:
    explicit ReleaseVehicleReservationUsecase(VehicleRepository& repository);

    void execute(std::string_view licensePlate) const;

private:
    VehicleRepository& repository_;
};


#endif //KOMISPO_RELEASEVEHICLERESERVATIONUSECASE_H
