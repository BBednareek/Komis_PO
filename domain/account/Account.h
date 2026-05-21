//
// Created by Mini on 20/05/2026.
//

#ifndef KOMISPO_ACCOUNT_H
#define KOMISPO_ACCOUNT_H
#include <string>


class Account {
public:
    Account(std::string login, std::string password);

    virtual ~Account() = default;

    [[nodiscard]] bool               isLoggedIn() const noexcept;
    [[nodiscard]] const std::string& getLogin()   const noexcept;

    [[nodiscard]] bool auth(std::string_view password) const noexcept;
                  void login();
                  void logout();

private:
    std::string login_;
    std::string password_;
    bool        loggedIn_;
};


#endif //KOMISPO_ACCOUNT_H
