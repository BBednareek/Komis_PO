//
// Created by Mini on 20/05/2026.
//

#include "CustomerAccount.h"

CustomerAccount::CustomerAccount(
        std::string name,
        std::string surname,
        std::string address,
        std::string login,
        const std::string& password,
        std::uint32_t
    ) : Account(
        std::move(login),
        password
    ),
    firstName_(std::move(name)),
    lastName_(std::move(surname)),
    address_(std::move(address)),
    purchasedVehiclesCount_(0){}

[[nodiscard]] std::vector<std::shared_ptr<Vehicle>> CustomerAccount::getReservedVehicleList() const noexcept { return vehicle_; }
void CustomerAccount::addReservedVehicle(const std::shared_ptr<Vehicle>& vehicle) { if (vehicle) vehicle_.push_back(vehicle); }

void CustomerAccount::removeReservedVehicle(const std::string& licensePlate) {
    const auto it = std::find_if(vehicle_.begin(), vehicle_.end(), [&](const std::shared_ptr<Vehicle>& vehicle) {
        return vehicle != nullptr && vehicle->getLicensePlate() == licensePlate;
    });

    if (it != vehicle_.end()) vehicle_.erase(it);
}

void CustomerAccount::incrementPurchasedVehicles() noexcept { ++purchasedVehiclesCount_; }
const std::string &CustomerAccount::getAddress() const noexcept { return address_; }
std::string CustomerAccount::getFullName() const { return firstName_ + ' ' + lastName_; }
