//
// Created by Mini on 20/05/2026.
//

#ifndef KOMISPO_ACCOUNT_H
#define KOMISPO_ACCOUNT_H
#include <string>


class Account {
public:
    virtual ~Account() = default;

    [[nodiscard]] bool               isLoggedIn() const;
    [[nodiscard]] const std::string& getLogin()   const;

protected:
    Account(std::string login, std::string password);

private:
    std::string login_;
    std::string password_;
    bool        loggedIn_;
};


#endif //KOMISPO_ACCOUNT_H
