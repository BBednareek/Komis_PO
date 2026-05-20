//
// Created by Mini on 20/05/2026.
//

#ifndef KOMISPO_CUSTOMERACCOUNT_H
#define KOMISPO_CUSTOMERACCOUNT_H
#include "Account.h"

class CustomerAccount : public Account {
public:
    CustomerAccount(
        std::string name,
        std::string surname,
        std::string address
    );

    void incrementPurchasedVehicles();

private:
    std::string      firstName_;
    std::string      lastName_;
    std::string      address_;
         uint32_t    purchasedVehiclesCount_;
};


#endif //KOMISPO_CUSTOMERACCOUNT_H
