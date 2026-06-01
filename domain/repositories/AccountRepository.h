#pragma once

#ifndef KOMISPO_IACCOUNTREPOSITORY_H
#define KOMISPO_IACCOUNTREPOSITORY_H

#include "../account/CustomerAccount.h"
#include "../account/EmployeeAccount.h"

class AccountRepository {
public:
    virtual ~AccountRepository() = default;

    virtual void addEmployee(std::shared_ptr<EmployeeAccount>) = 0;
    virtual void addCustomer(std::shared_ptr<CustomerAccount>) = 0;
    virtual void clear() = 0;
    virtual std::shared_ptr<CustomerAccount> findCustomerByLogin(std::string_view login) = 0;
    virtual std::shared_ptr<EmployeeAccount> findEmployeeByLogin(std::string_view login) = 0;
    [[nodiscard]] virtual std::vector<std::shared_ptr<EmployeeAccount>> getAllEmployees() const = 0;
    [[nodiscard]] virtual std::vector<std::shared_ptr<CustomerAccount>> getAllCustomers() const = 0;
};


#endif //KOMISPO_IACCOUNTREPOSITORY_H
