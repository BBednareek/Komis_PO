#ifndef KOMISPO_CUSTOMERLOGINUSECASE_H
#define KOMISPO_CUSTOMERLOGINUSECASE_H
#include "../../../domain/repositories/AccountRepository.h"


class CustomerLoginUsecase final {
public:
    explicit CustomerLoginUsecase (AccountRepository& repository);

    [[nodiscard]] std::shared_ptr<Account> execute(std::string_view login, std::string_view password) const;

private:
    AccountRepository& repository_;
};


#endif //KOMISPO_CUSTOMERLOGINUSECASE_H
