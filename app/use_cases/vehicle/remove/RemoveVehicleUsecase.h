#ifndef KOMISPO_REMOVEVEHICLEUSECASE_H
#define KOMISPO_REMOVEVEHICLEUSECASE_H

#include "../../../../domain/repositories/VehicleRepository.h"

class RemoveVehicleUsecase final {
public:
    explicit RemoveVehicleUsecase(VehicleRepository& repository);

    void execute(std::string_view licensePlate) const;

private:
    VehicleRepository& repository_;
};


#endif //KOMISPO_REMOVEVEHICLEUSECASE_H
