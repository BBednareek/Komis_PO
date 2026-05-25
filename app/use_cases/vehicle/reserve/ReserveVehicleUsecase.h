#ifndef KOMISPO_RESERVEVEHICLEUSECASE_H
#define KOMISPO_RESERVEVEHICLEUSECASE_H
#include "../../../../domain/account/CustomerAccount.h"
#include "../../../../domain/repositories/AccountRepository.h"
#include "../../../../domain/repositories/TaskRepository.h"
#include "../../../../domain/repositories/VehicleRepository.h"


class ReserveVehicleUsecase final {
public:
    ReserveVehicleUsecase(
        VehicleRepository&  vehicleRepository,
        AccountRepository&  accountRepository,
        TaskRepository&     taskRepository
        );

    void execute(const CustomerAccount& customer, std::string_view licensePlate) const;

private:
    [[nodiscard]] std::shared_ptr<EmployeeAccount> findAvailableEmployees() const;

    VehicleRepository& vehicleRepository_;
    TaskRepository& taskRepository_;
    AccountRepository& accountRepository_;
};


#endif //KOMISPO_RESERVEVEHICLEUSECASE_H
