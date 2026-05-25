#include "AccountRepositoryImpl.h"
#include <memory>
#include "../../domain/common/ListTypes.h"
#include "../../domain/repositories/AccountRepository.h"
#include "../../domain/common/Exceptions.h"

void AccountRepositoryImpl::addEmployee(const std::shared_ptr<EmployeeAccount> account)  { employeeAccountList_.pushBack(account); }
void AccountRepositoryImpl::addCustomer(const std::shared_ptr<CustomerAccount> account)  { customerAccountList_.pushBack(account); }

std::shared_ptr<CustomerAccount> AccountRepositoryImpl::findCustomerByLogin(const std::string_view login) {
    const auto accountPtr = customerAccountList_.findData([&](const std::shared_ptr<CustomerAccount>& cA) {
        return cA->getLogin() == login;
    });

    if (accountPtr) return accountPtr;
    throw AuthenticationException("Nie znaleziono uzytkownika");
}

std::shared_ptr<EmployeeAccount> AccountRepositoryImpl::findEmployeeByLogin(const std::string_view login) {
    const auto accountPtr = employeeAccountList_.findData([&](const std::shared_ptr<EmployeeAccount>& eA) {
        return eA -> getLogin() == login;
    });

    if (accountPtr) return accountPtr;
    throw AuthenticationException("Nie znaleziono uzytkownika");
}