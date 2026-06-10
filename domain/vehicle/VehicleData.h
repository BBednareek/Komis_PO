#pragma once

#ifndef KOMISPO_VEHICLEDATA_H
#define KOMISPO_VEHICLEDATA_H
#include <cstdint>
#include <string>
#include <utility>
#include "FuelType.h"
#include "VehicleStatus.h"

class VehicleData final {
public:
    [[nodiscard]] std::string   getBrand()              const noexcept { return brand_; }
    [[nodiscard]] std::string   getModel()              const noexcept { return model_; }
    [[nodiscard]] std::string   getLicensePlate()       const noexcept { return licensePlate_; }
    [[nodiscard]] std::string   displayName()           const noexcept { return brand_ + ' ' + model_; }
    [[nodiscard]] std::string   getExpirationDate()     const noexcept { return expirationDate_; }
    [[nodiscard]] std::uint32_t getHorsePower()         const noexcept { return horsePower_; }
    [[nodiscard]] std::uint32_t getproductionYear()     const noexcept { return productionYear_; }
    [[nodiscard]] double        getEngingeCapacity()    const noexcept { return engineCapacity_; }
    [[nodiscard]] FuelType      getFuelType()           const noexcept { return fuelType_; }
    [[nodiscard]] VehicleStatus getVehicleStatus()      const noexcept { return vehicleStatus_; }

    VehicleData(
    std::string brand,
    std::string model,
    std::string licensePlate,
    const std::uint32_t horsePower,
    const std::uint32_t productionYear,
    std::string expirationDate,
    const double engineCapacity,
    const FuelType fuelType,
    VehicleStatus vehicleStatus
    ) :
    brand_(std::move(brand)),
    model_(std::move(model)),
    licensePlate_(std::move(licensePlate)),
    horsePower_(horsePower),
    productionYear_(productionYear),
    expirationDate_(std::move(expirationDate)),
    engineCapacity_(engineCapacity),
    fuelType_(fuelType),
    vehicleStatus_(vehicleStatus) {}

private:
    std::string brand_;
    std::string model_;
    std::string licensePlate_;
    std::uint32_t horsePower_;
    std::uint32_t productionYear_;
    std::string expirationDate_;
    double engineCapacity_;
    FuelType fuelType_;
    VehicleStatus vehicleStatus_;

};

#endif //KOMISPO_VEHICLEDATA_H
