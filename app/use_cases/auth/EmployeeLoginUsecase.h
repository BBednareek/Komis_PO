//
// Created by Mini on 25/05/2026.
//

#ifndef KOMISPO_EMPLOYEELOGINUSECASE_H
#define KOMISPO_EMPLOYEELOGINUSECASE_H
#include <memory>

#include "../../../domain/repositories/AccountRepository.h"

class EmployeeLoginUsecase final {
public:
    explicit EmployeeLoginUsecase (AccountRepository& repository);

    [[nodiscard]] std::shared_ptr<Account> execute(std::string_view login, std::string_view password) const;

private:
    AccountRepository& repository_;
};



#endif //KOMISPO_EMPLOYEELOGINUSECASE_H
