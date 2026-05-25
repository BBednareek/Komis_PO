#include "EmployeeLoginUsecase.h"

#include "../../../domain/common/Exceptions.h"

EmployeeLoginUsecase::EmployeeLoginUsecase (AccountRepository& repository) : repository_(repository) {}

[[nodiscard]] std::shared_ptr<Account> EmployeeLoginUsecase::execute(const std::string_view login, const std::string_view password) const {
    auto account = repository_.findEmployeeByLogin(login);

    if (account == nullptr)         throw AuthenticationException("Brak uzytkownika w bazie");
    if (!account -> auth(password)) throw AuthenticationException("Zle haslo");

    account -> login();

    return account;
}