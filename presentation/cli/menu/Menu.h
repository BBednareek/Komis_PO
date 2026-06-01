#ifndef KOMISPO_MENU_H
#define KOMISPO_MENU_H

#include <string>

enum class MainAction : std::uint8_t {
    CustomerLogin   = 1,
    EmployeeLogin   = 2,
    ShowVehicles    = 3,
    Exit            = 0
};

enum class CustomerAction : std::uint8_t {
    ShowVehicles    = 1,
    ReserveVehicle  = 2,
    SearchVehicle   = 3,
    CollectVehicle  = 4,
    ShowData        = 5,
    ChangeAddress   = 6,
    Logout          = 0,
};

enum class EmployeeAction : std::uint8_t {
    ShowVehicles        = 1,
    AddVehicle          = 2,
    RemoveVehicle       = 3,
    MarkReadyForPickup  = 4,
    ReleaseReservation  = 5,
    ShowTasks           = 6,
    CompleteTask        = 7,
    ShowEmployeeData    = 8,
    Logout              = 0
};

class Menu final {
public:
    [[nodiscard]] static MainAction     promptMainAction();
    static        CustomerAction promptCustomerAction() ;
    static        EmployeeAction promptEmployeeAction() ;

    static std::string prompt(const std::string& label) ;
    static void waitForEnter() ;

private:
    static int readInt() ;
};


#endif //KOMISPO_MENU_H
