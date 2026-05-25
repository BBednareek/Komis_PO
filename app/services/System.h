#ifndef KOMISPO_SYSTEM_H
#define KOMISPO_SYSTEM_H
#include <memory>

#include "../../domain/repositories/AccountRepository.h"
#include "../../domain/repositories/VehicleRepository.h"


class System final {
public:
    System(std::unique_ptr<AccountRepository> accountRepository, std::unique_ptr<VehicleRepository> vehicleRepository);

    [[nodiscard]] AccountRepository& accounts() const noexcept;
    [[nodiscard]] VehicleRepository& vehicles() const noexcept;

private:
    std::unique_ptr<AccountRepository> accountRepository_;
    std::unique_ptr<VehicleRepository> vehicleRepository_;
};


#endif //KOMISPO_SYSTEM_H
