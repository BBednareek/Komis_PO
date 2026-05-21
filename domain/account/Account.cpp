#include "Account.h"

Account::Account(std::string login, const std::string& password) :
    login_(std::move(login)),
    password_(std::to_string(std::hash<std::string>{}(password)))
        { loggedIn_ = false; }

[[nodiscard]] bool Account::isLoggedIn() const noexcept { return loggedIn_; }

[[nodiscard]] const std::string& Account::getLogin() const noexcept { return login_; }

[[nodiscard]] bool Account::auth(const std::string_view password) const noexcept {
    return password_ == std::to_string(std::hash<std::string>{}(std::string(password)));
}

void Account::login()   { loggedIn_ = true;  }
void Account::logout()  { loggedIn_ = false; }