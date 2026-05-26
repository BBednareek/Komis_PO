#ifndef KOMISPO_VEHICLEREPOSITORYIMPL_H
#define KOMISPO_VEHICLEREPOSITORYIMPL_H

#include <memory>
#include <vector>
#include "../../../domain/repositories/VehicleRepository.h"
#include "../../../domain/common/ListTypes.h"

class VehicleRepositoryImpl final : public VehicleRepository {
public:
    void add(std::shared_ptr<Vehicle> vehicle) override;
    void remove(std::string_view registration) override;
    void displayAllVehicles() const override;

    std::vector<VehicleData> searchForCar(const VehicleSearchCriteria &criteria) override;
    std::shared_ptr<Vehicle> findByRegistration(std::string_view registration) override ;
    [[nodiscard]] std::vector<VehicleData> getAllVehicles() const override;

private:
    VehicleList vehicleList_;
};

#endif //KOMISPO_VEHICLEREPOSITORYIMPL_H
