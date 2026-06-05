#include "Vehicle.h"

#include "../common/Exceptions.h"

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

void Vehicle::reserve() {
        if (!isAvailableForReservation()) throw VehicleException("Pojazd nie jest dostepny do rezerwacji");
        vehicleStatus_ = VehicleStatus::Reserved;
}

void Vehicle::markReadyForPickup() {
        if (vehicleStatus_ != VehicleStatus::Reserved) throw VehicleException("Tylko zarezerowowany pojazd moze byc gotowy do odbioru");
        vehicleStatus_ = VehicleStatus::ReadyForPickup;
}
void Vehicle::release() {
        if (vehicleStatus_ == VehicleStatus::ForSale) throw VehicleException("Pojazd jest juz dostepny na sprzedaz");
        vehicleStatus_ = VehicleStatus::ForSale;
}

const std::string &Vehicle::getLicensePlate() const noexcept { return licensePlate_; }
VehicleStatus Vehicle::getVehicleStatus() const noexcept { return vehicleStatus_; }
VehicleData Vehicle::getVehicleData() const {
        return {
                 brand_,
                 model_,
                 licensePlate_,
                 horsePower_,
                 productionYear_,
                expirationDate_,
                 engineCapacity_,
                 fuelType_,
                 vehicleStatus_
        };
}

[[nodiscard]] bool Vehicle::isAvailableForReservation() const noexcept { return vehicleStatus_ == VehicleStatus::ForSale; }
