//
// Created by Mini on 21/05/2026.
//

#ifndef KOMISPO_EXCEPTIONS_H
#define KOMISPO_EXCEPTIONS_H

#include <stdexcept>

class AuthenticationException final : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class VehicleException final : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif //KOMISPO_EXCEPTIONS_H
