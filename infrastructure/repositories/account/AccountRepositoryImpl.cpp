#include "AccountRepositoryImpl.h"
#include <cstdint>
#include <memory>
#include "../../../domain/common/ListTypes.h"
#include "../../../domain/repositories/AccountRepository.h"
#include "../../../domain/common/Exceptions.h"

namespace {
    constexpr std::uint32_t employeeConstraint = 10;
    constexpr std::uint32_t customerConstraint = 200;
}

void AccountRepositoryImpl::addEmployee(const std::shared_ptr<EmployeeAccount> account) {
    if (account == nullptr) throw ValidationException("Nie mozna dodac pustego pracownika");
    if (static_cast<uint32_t>(getAllEmployees().size()) >= employeeConstraint) throw ValidationException("Osiagnieto limit pracownikow");

    const auto existingAccount = employeeAccountList_.findData([&](const std::shared_ptr<EmployeeAccount>& candidate) {
       return candidate != nullptr && candidate -> getLogin() == account -> getLogin();
    });

    if (existingAccount != nullptr) throw ValidationException("Pracownik o podanym loginie juz istnieje");

    employeeAccountList_.pushBack(account);
}

void AccountRepositoryImpl::addCustomer(const std::shared_ptr<CustomerAccount> account) {
    if (account == nullptr) throw ValidationException("Nie mozna dodac pustego konsumenta");
    if (static_cast<uint32_t>(getAllCustomers().size()) >= customerConstraint) throw ValidationException("Osiagnieto limit konsumentow");

    const auto existingAccount = customerAccountList_.findData([&](const std::shared_ptr<CustomerAccount>& candidate) {
       return candidate != nullptr && candidate -> getLogin() == account -> getLogin();
    });

    if (existingAccount != nullptr) throw ValidationException("Konsument o podanym loginie juz istnieje");

    customerAccountList_.pushBack(account);
}

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

[[nodiscard]] std::vector<std::shared_ptr<EmployeeAccount>> AccountRepositoryImpl::getAllEmployees() const { return employeeAccountList_.getAllData(); }
[[nodiscard]] std::vector<std::shared_ptr<CustomerAccount>> AccountRepositoryImpl::getAllCustomers() const { return customerAccountList_.getAllData(); }
