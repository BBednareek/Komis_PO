#include "System.h"

System::System(
    std::unique_ptr<AccountRepository> accountRepository,
    std::unique_ptr<VehicleRepository> vehicleRepository
    ) :
    accountRepository_(std::move(accountRepository)),
    vehicleRepository_(std::move(vehicleRepository)) {}

AccountRepository& System::accounts() const noexcept { return *accountRepository_; }
VehicleRepository& System::vehicles() const noexcept { return *vehicleRepository_; }