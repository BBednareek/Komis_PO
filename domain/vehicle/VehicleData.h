#pragma once

#ifndef KOMISPO_VEHICLEDATA_H
#define KOMISPO_VEHICLEDATA_H
#include <string>
#include "FuelType.h"
#include "VehicleStatus.h"

struct VehicleData final {
    std::string brand;
    std::string model;
    std::string licensePlate;
    std::uint32_t horsePower {};
    std::uint32_t productionYear {};
    std::string expirationDate;
    double engineCapacity {};
    FuelType fuelType {FuelType::Petrol};
    VehicleStatus vehicleStatus {VehicleStatus::ForSale};

    [[nodiscard]] std::string displayName() const { return brand + ' ' + model; }
};

#endif //KOMISPO_VEHICLEDATA_H
