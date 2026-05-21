//
// Created by Mini on 21/05/2026.
//

#include <memory>

#include "../../domain/common/Types.h"
#include "../../domain/repositories/IAccountRepository.h"

class IMAccountRepository final : public IAccountRepository {
public:
    void addEmployee(std::shared_ptr<EmployeeAccount> account) override {
        employeeAccountList_.pushBack(account);
    }

private:
    EmployeeAccountList employeeAccountList_;
    CustomerAccountList customerAccountList_;
};