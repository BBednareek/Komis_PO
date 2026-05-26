#ifndef KOMISPO_SYSTEM_H
#define KOMISPO_SYSTEM_H
#include <memory>

#include "../../domain/repositories/AccountRepository.h"
#include "../../domain/repositories/TaskRepository.h"
#include "../../domain/repositories/VehicleRepository.h"


class System final {
public:
    System(
        std::unique_ptr<AccountRepository>  accountRepository,
        std::unique_ptr<VehicleRepository>  vehicleRepository,
        std::unique_ptr<TaskRepository>     taskRepository
        );
    // Klasa System posiada repozytoria przez std::unique_ptr,
    // dlatego po usunięciu System wszystkie repozytoria i przechowywane dane są automatycznie usuwane zgodnie z RAII.
    ~System();

    [[nodiscard]] AccountRepository& accounts() const noexcept;
    [[nodiscard]] VehicleRepository& vehicles() const noexcept;
    [[nodiscard]] TaskRepository&    tasks()    const noexcept;

private:
    std::unique_ptr<AccountRepository> accountRepository_;
    std::unique_ptr<TaskRepository> taskRepository_;
    std::unique_ptr<VehicleRepository> vehicleRepository_;
};


#endif //KOMISPO_SYSTEM_H
