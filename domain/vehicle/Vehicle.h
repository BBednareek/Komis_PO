#pragma once

#ifndef KOMISPO_VEHICLE_H
#define KOMISPO_VEHICLE_H
#include <string>
#include "FuelType.h"
#include "VehicleStatus.h"
#include "VehicleData.h"
#include <vector>

class Vehicle {
public:
    Vehicle(
        std::string brand,
        std::string model,
        std::string licensePlate,
        std::uint32_t horsePower,
        std::uint32_t productionYear,
        std::string expirationDate,
        double engineCapacity,
        FuelType fuelType
        );

    [[nodiscard]] const std::string& getLicensePlate() const noexcept;
    [[nodiscard]] VehicleStatus getVehicleStatus() const noexcept;
    [[nodiscard]] std::string getVehicleName() const;
    void reserve();
    void markReadyForPickup();
    void release();
    [[nodiscard]] bool isAvailableForReservation() const noexcept;
    [[nodiscard]] VehicleData getVehicleData() const;
    friend std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle);

private:
    std::string   brand_;
    std::string   model_;
    std::string   licensePlate_;
    std::string   expirationDate_;
    std::uint32_t productionYear_;
    std::uint32_t horsePower_;
    double        engineCapacity_;
    FuelType      fuelType_;
    VehicleStatus vehicleStatus_ { VehicleStatus::ForSale };
};

#endif //KOMISPO_VEHICLE_H
