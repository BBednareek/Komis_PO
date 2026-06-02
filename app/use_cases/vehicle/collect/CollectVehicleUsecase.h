#ifndef KOMISPO_COLLECTVEHICLEUSECASE_H
#define KOMISPO_COLLECTVEHICLEUSECASE_H

#include <memory>
#include <string_view>

#include "../../../../domain/account/CustomerAccount.h"
#include "../../../../domain/repositories/TaskRepository.h"
#include "../../../../domain/repositories/VehicleRepository.h"

class CollectVehicleUsecase final {
public:
    explicit CollectVehicleUsecase(
        VehicleRepository& vehicleRepository,
        TaskRepository& taskRepository
    );

    void execute(const std::shared_ptr<CustomerAccount>& customer, std::string_view licensePlate) const;

private:
    VehicleRepository& vehicleRepository_;
    TaskRepository& taskRepository_;
};

#endif //KOMISPO_COLLECTVEHICLEUSECASE_H
