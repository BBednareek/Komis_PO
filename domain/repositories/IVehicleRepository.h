#pragma once

#ifndef KOMISPO_IVEHICLEREPOSITORY_H
#define KOMISPO_IVEHICLEREPOSITORY_H


#include "../vehicle/Vehicle.h"
#include <string_view>

class IVehicleRepository {
public:
    virtual ~IVehicleRepository() = default;

    virtual void add(std::shared_ptr<Vehicle>) = 0;
    virtual void remove(std::string_view registration) = 0;
    virtual VehicleData findByRegistration(std::string_view registration) = 0;
    virtual std::vector<VehicleData> getAllVehicles() = 0;
    virtual void displayAllVehicles() const = 0;
};


#endif //KOMISPO_IVEHICLEREPOSITORY_H
