#pragma once

#ifndef KOMISPO_VEHICLE_H
#define KOMISPO_VEHICLE_H
#include <memory>
#include <string>
#include "FuelType.h"
#include "VehicleStatus.h"
#include "VehicleData.h"
#include <vector>

#include "../account/CustomerAccount.h"

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
        FuelType fuelType,
        const std::shared_ptr<CustomerAccount>& customer
        );

    [[nodiscard]] const std::string& getLicensePlate() const noexcept;
    [[nodiscard]] VehicleStatus getVehicleStatus() const noexcept;
    void reserve();
    void markReadyForPickup();
    void release();
    [[nodiscard]] bool isAvailableForReservation() const noexcept;
    [[nodiscard]] VehicleData getVehicleData() const;
    [[nodiscard]] const std::weak_ptr<CustomerAccount>& getAssignedCustomer() const;

private:
    std::weak_ptr<CustomerAccount> customer_;
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
