//
// Created by Mini on 20/05/2026.
//

#include "CustomerAccount.h"

CustomerAccount::CustomerAccount(
        std::string name,
        std::string surname,
        std::string address,
        std::string login,
        const std::string& password
    ) : Account(
        std::move(login),
        password
        ),
        firstName_(std::move(name)),
        lastName_(std::move(surname)),
        address_(std::move(address)) {}

void CustomerAccount::incrementPurchasedVehicles() noexcept { ++purchasedVehiclesCount_; }
