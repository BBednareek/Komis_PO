#ifndef KOMISPO_RESERVEVEHICLEUSECASE_H
#define KOMISPO_RESERVEVEHICLEUSECASE_H
#include "../../../domain/account/CustomerAccount.h"
#include "../../../domain/repositories/VehicleRepository.h"


class ReserveVehicleUsecase final {
public:
    explicit ReserveVehicleUsecase(VehicleRepository& repository);

    void execute(std::string_view licensePlate) const;

private:
    VehicleRepository& repository_;
};


#endif //KOMISPO_RESERVEVEHICLEUSECASE_H
