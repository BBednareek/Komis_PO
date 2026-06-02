//
// Created by Mini on 21/05/2026.
//

#ifndef KOMISPO_CONSOLEAPPLICATION_H
#define KOMISPO_CONSOLEAPPLICATION_H
#include "../menu/Menu.h"
#include "../../../app/services/System.h"
#include "../../../app/use_cases/auth/customer/CustomerLoginUsecase.h"
#include "../../../app/use_cases/auth/employee/EmployeeLoginUsecase.h"
#include "../../../app/use_cases/vehicle/reserve/ReserveVehicleUsecase.h"
#include "../../../app/use_cases/task/CompleteTaskUsecase.h"
#include "../../../app/use_cases/vehicle/add/AddVehicleUsecase.h"
#include "../../../app/use_cases/vehicle/remove/RemoveVehicleUsecase.h"
#include "../../../app/use_cases/vehicle/markReady/MarkVehicleReadyForPickupUsecase.h"
#include "../../../app/use_cases/vehicle/releaseVehicle/ReleaseVehicleReservationUsecase.h"
#include "../../../app/use_cases/vehicle/search/SearchVehicleUsecase.h"
#include "../../../app/use_cases/vehicle/collect/CollectVehicleUsecase.h"


class ConsoleApplication final {
public:
    explicit ConsoleApplication(System& system);
    void run() const;

private:
    void handleMainAction(MainAction action) const;
    void handleCustomerLogin() const;
    void handleEmployeeLogin() const;
    void customerPanel(const std::shared_ptr<Account>& account) const;
    void employeePanel(const std::shared_ptr<Account>& account) const;
    void showVehicles() const;
    void showCustomerData(const CustomerAccount& customer) const;
    void showEmployeeData(const EmployeeAccount& employee) const;
    void reserveVehicleFlow(const std::shared_ptr<CustomerAccount>& customer) const;
    void collectVehicleFlow(const std::shared_ptr<CustomerAccount>& customer) const;
    [[nodiscard]] bool canCollectVehicle(const CustomerAccount& customer) const;
    void addVehicleFlow() const;
    void removeVehicleFlow() const;
    void markReadyForPickupFlow(const EmployeeAccount& employee) const;
    void releaseReservationFlow(EmployeeAccount& employee) const;

    static void showEmployeeTasks(const EmployeeAccount& employee);
    void completeEmployeeTaskFlow(EmployeeAccount& employee) const;

    static void printMessage(const std::string& message);

    void searchVehicles() const;
    [[nodiscard]] static std::shared_ptr<CustomerAccount> requireCustomerAccount(const std::shared_ptr<Account>& account);
    [[nodiscard]] static EmployeeAccount& requireEmployeeAccount(const std::shared_ptr<Account>& account);

    static double readDouble(const std::string& label) ;
    [[nodiscard]] static std::uint32_t readUnsigned(const std::string& label);

    System& system_;
    Menu menu_;
    CustomerLoginUsecase customerLoginUseCase_;
    SearchVehicleUsecase searchVehicleUseCase_;
    EmployeeLoginUsecase employeeLoginUseCase_;
    CompleteTaskUsecase completeTaskUseCase_;
    AddVehicleUsecase addVehicleUseCase_;
    RemoveVehicleUsecase removeVehicleUseCase_;
    MarkVehicleReadyForPickupUsecase markVehicleReadyForPickupUseCase_;
    ReleaseVehicleReservationUsecase releaseVehicleReservationUseCase_;
    ReserveVehicleUsecase reserveVehicleUseCase_;
    CollectVehicleUsecase collectVehicleUseCase_;
};


#endif //KOMISPO_CONSOLEAPPLICATION_H
