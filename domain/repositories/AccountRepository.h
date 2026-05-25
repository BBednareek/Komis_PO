#pragma once

#ifndef KOMISPO_IACCOUNTREPOSITORY_H
#define KOMISPO_IACCOUNTREPOSITORY_H

#include "../account/CustomerAccount.h"
#include "../account/EmployeeAccount.h"

class AccountRepository {
public:
    const int employeeConstraint { 10 };
    const int customerConstraint { 200 };

    virtual ~AccountRepository() = default;

    virtual void addEmployee(std::shared_ptr<EmployeeAccount>) = 0;
    virtual void addCustomer(std::shared_ptr<CustomerAccount>) = 0;
    virtual std::shared_ptr<CustomerAccount> findCustomerByLogin(std::string_view login) = 0;
    virtual std::shared_ptr<EmployeeAccount> findEmployeeByLogin(std::string_view login) = 0;
};


#endif //KOMISPO_IACCOUNTREPOSITORY_H
