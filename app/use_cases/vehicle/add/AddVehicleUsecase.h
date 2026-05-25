#ifndef KOMISPO_ADDVEHICLEUSECASE_H
#define KOMISPO_ADDVEHICLEUSECASE_H
#include "../../../../domain/repositories/VehicleRepository.h"

#include <memory>
class AddVehicleUsecase final {
public:
    explicit AddVehicleUsecase(VehicleRepository& repository);

    void execute(std::shared_ptr<Vehicle> vehicle) const;

private:
    VehicleRepository& vehicleRepository_;
};


#endif //KOMISPO_ADDVEHICLEUSECASE_H
