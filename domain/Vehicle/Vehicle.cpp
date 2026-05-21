//
// Created by Mini on 20/05/2026.
//

#include "Vehicle.h"

Vehicle::Vehicle(
        std::string         brand,
        std::string         model,
        std::string         licensePlate,
        const std::uint32_t horsePower,
        const std::uint32_t productionYear,
        std::string         expirationDate, //Data wygasniecia badan okresowych
        const double        engineCapacity,
        const FuelType      fuelType
        ) :
        brand_(std::move(brand)),
        model_(std::move(model)),
        licensePlate_(std::move(licensePlate)),
        expirationDate_(std::move(expirationDate)),
        productionYear_(productionYear),
        horsePower_(horsePower),
        engineCapacity_(engineCapacity),
        fuelType_(fuelType) {}

void Vehicle::reserve() { vehicleStatus_ = VehicleStatus::Reserved;}
void Vehicle::markReadyForPickup() { vehicleStatus_ = VehicleStatus::ReadyForPickup; }
void Vehicle::release() { vehicleStatus_ = VehicleStatus::ForSale; }

const std::string &Vehicle::getLicensePlate() const noexcept { return licensePlate_; }
std::string Vehicle::getVehicleName() const { return brand_ + model_; }
VehicleStatus Vehicle::getVehicleStatus() const noexcept { return vehicleStatus_; }
VehicleData Vehicle::getVehicleData() {
        return{
                getVehicleName(),
                licensePlate_,
                horsePower_,
                productionYear_,
                engineCapacity_,
                fuelType_
        };
}

