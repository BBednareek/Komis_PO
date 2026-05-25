#include "CustomerLoginUsecase.h"

#include "../../../../domain/common/Exceptions.h"

CustomerLoginUsecase::CustomerLoginUsecase (AccountRepository& repository) : repository_(repository) {}

std::shared_ptr<Account> CustomerLoginUsecase::execute(const std::string_view login, const std::string_view password) const {
    auto account = repository_.findCustomerByLogin(login);

    if (!account -> auth(password)) throw AuthenticationException("Zle haslo");

    account -> login();

    return account;
}
