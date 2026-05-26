#pragma once

#ifndef KOMISPO_IVEHICLEREPOSITORY_H
#define KOMISPO_IVEHICLEREPOSITORY_H


#include "../vehicle/Vehicle.h"
#include <string_view>
#include <vector>

#include "../vehicle/VehicleSearchCriteria.h"

class VehicleRepository {
public:
    virtual ~VehicleRepository() = default;

    virtual std::vector<VehicleData> searchForCar(const VehicleSearchCriteria& criteria) = 0;
    virtual std::shared_ptr<Vehicle> findByRegistration(std::string_view registration) = 0;
    [[nodiscard]] virtual std::vector<VehicleData> getAllVehicles() const = 0;
    virtual void remove(std::string_view registration) = 0;
    virtual void add(std::shared_ptr<Vehicle>) = 0;
    virtual void displayAllVehicles() const = 0;
};


#endif //KOMISPO_IVEHICLEREPOSITORY_H
