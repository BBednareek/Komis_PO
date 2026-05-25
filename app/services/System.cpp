#include "System.h"

System::System(
    std::unique_ptr<AccountRepository> accountRepository,
    std::unique_ptr<VehicleRepository> vehicleRepository,
    std::unique_ptr<TaskRepository>    taskRepository
    ) :
    accountRepository_(std::move(accountRepository)),
    taskRepository_(std::move(taskRepository)),
    vehicleRepository_(std::move(vehicleRepository)) {}

AccountRepository&  System::accounts()   const noexcept { return *accountRepository_; }
VehicleRepository&  System::vehicles()   const noexcept { return *vehicleRepository_; }
TaskRepository&     System::tasks()      const noexcept { return *taskRepository_; }
