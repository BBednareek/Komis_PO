#include <memory>

#include "../../domain/common/ListTypes.h"
#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/common/Exceptions.h"

class IMAccountRepository final : public IAccountRepository {
public:
    void addEmployee(const std::shared_ptr<EmployeeAccount> account) override { employeeAccountList_.pushBack(account); }
    void addCustomer(const std::shared_ptr<CustomerAccount> account) override { customerAccountList_.pushBack(account); }

    std::shared_ptr<CustomerAccount> findCustomerByLogin(const std::string_view login) override {
        const auto accountPtr = customerAccountList_.findData([&](const std::shared_ptr<CustomerAccount>& cA) {
            return cA->getLogin() == login;
        });

        if (accountPtr) return accountPtr;
        throw AuthenticationException("Nie znaleziono uzytkownika");
    }

    std::shared_ptr<EmployeeAccount> findEmployeeByLogin(const std::string_view login) override {
        const auto accountPtr = employeeAccountList_.findData([&](const std::shared_ptr<EmployeeAccount>& eA) {
            return eA -> getLogin() == login;
        });

        if (accountPtr) return accountPtr;
        throw AuthenticationException("Nie znaleziono uzytkownika");
    }

private:
    EmployeeAccountList employeeAccountList_;
    CustomerAccountList customerAccountList_;
};