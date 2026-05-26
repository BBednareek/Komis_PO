#include "Vehicle.h"
#include <iostream>

#include "../common/Exceptions.h"

namespace vehicle {
        const char* toString(const FuelType fuelType) {
                switch (fuelType) {
                        case FuelType::Petrol: return "benzyna";
                        case FuelType::Diesel: return "diesel";
                        case FuelType::Hybrid: return "hybryda";
                        case FuelType::Electric: return "elektryczny";
                        case FuelType::LPG: return "lpg";
                }

                return "nieznany";
}

        const char* toString(const VehicleStatus status) {
                switch (status) {
                        case VehicleStatus::Reserved: return "zarezerwowany";
                        case VehicleStatus::ReadyForPickup: return "gotowy do odbioru";
                        case VehicleStatus::ForSale: return "na sprzedaz";
                }
                return "nieznany";
        }
}

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
std::string Vehicle::getVehicleName() const { return brand_ + model_; }
VehicleStatus Vehicle::getVehicleStatus() const noexcept { return vehicleStatus_; }
VehicleData Vehicle::getVehicleData() const {
        return VehicleData {
                .brand = brand_,
                .model = model_,
                .licensePlate = licensePlate_,
                .horsePower = horsePower_,
                .productionYear = productionYear_,
                .expirationDate = expirationDate_,
                .engineCapacity = engineCapacity_,
                .fuelType = fuelType_,
                .vehicleStatus = vehicleStatus_
        };
}

[[nodiscard]] bool Vehicle::isAvailableForReservation() const noexcept { return vehicleStatus_ == VehicleStatus::ForSale; }

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
        os << vehicle.brand_ << ' ' << vehicle.model_
        << " | rejestracja: " << vehicle.licensePlate_
        << " | moc: " << vehicle.horsePower_ << " KM"
        << " | rok: " << vehicle.productionYear_
        << " | pojemnosc skokowa: " << vehicle.engineCapacity_
        << " | paliwo: " << vehicle::toString(vehicle.fuelType_)
        << " | data waznosci badania okresowego: " << vehicle.expirationDate_
        << " | status: " << vehicle::toString(vehicle.vehicleStatus_);

        return os;

}