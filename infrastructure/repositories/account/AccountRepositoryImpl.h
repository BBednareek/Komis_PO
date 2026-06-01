#ifndef KOMISPO_ACCOUNTREPOSITORYIMPL_H
#define KOMISPO_ACCOUNTREPOSITORYIMPL_H
#include <memory>
#include "../../../domain/common/ListTypes.h"
#include "../../../domain/repositories/AccountRepository.h"

class AccountRepositoryImpl final : public AccountRepository {
public:
    void addEmployee( std::shared_ptr<EmployeeAccount> account) override;
    void addCustomer( std::shared_ptr<CustomerAccount> account) override;
    void clear() override;

    std::shared_ptr<CustomerAccount> findCustomerByLogin(std::string_view login) override;

    std::shared_ptr<EmployeeAccount> findEmployeeByLogin(std::string_view login) override ;
    [[nodiscard]] std::vector<std::shared_ptr<EmployeeAccount>> getAllEmployees() const override;
    [[nodiscard]] std::vector<std::shared_ptr<CustomerAccount>> getAllCustomers() const override;

private:
    EmployeeAccountList employeeAccountList_;
    CustomerAccountList customerAccountList_;
};

#endif //KOMISPO_ACCOUNTREPOSITORYIMPL_H
