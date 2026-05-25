//
// Created by Mini on 20/05/2026.
//
#ifndef KOMISPO_CUSTOMERACCOUNT_H
#define KOMISPO_CUSTOMERACCOUNT_H
#include "Account.h"


class CustomerAccount final : public Account {
public:
    CustomerAccount(
        std::string name,
        std::string surname,
        std::string address,
        std::string login,
        const std::string& password
    );

    void incrementPurchasedVehicles() noexcept;
    [[nodiscard]] const std::string& getFirstName() const noexcept;
    [[nodiscard]] const std::string& getLastName() const noexcept;
    [[nodiscard]] const std::string& getAddress() const noexcept;
    [[nodiscard]] std::string getFullName() const;
    [[nodiscard]] std::uint32_t getPurchasedVehiclesCount() const noexcept;

private:
    std::string      firstName_;
    std::string      lastName_;
    std::string      address_;
    std::uint32_t    purchasedVehiclesCount_ {0};
};


#endif //KOMISPO_CUSTOMERACCOUNT_H
