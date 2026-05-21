//
// Created by Mini on 21/05/2026.
//

#ifndef KOMISPO_IACCOUNTREPOSITORY_H
#define KOMISPO_IACCOUNTREPOSITORY_H

#include "../account/Account.h"

class IAccountRepository {
public:
    virtual ~IAccountRepository() = default;

    virtual void add(std::shared_ptr<Account>) = 0;
    virtual std::shared_ptr<Account> findByLogin(std::string_view login) = 0;
};


#endif //KOMISPO_IACCOUNTREPOSITORY_H
