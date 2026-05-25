#include <iostream>
#include "../infrastructure/repositories/AccountRepostioryImpl.cpp"


int main() {

    auto accountRepository = std::make_unique<AccountRepositoryImpl>();
    auto vehicleRepository = std::make_unique<VehicleRepositoryImpl>();

    System system(std::move(accountRepository), std::move(vehicleRepository));

    //Test add buyer
    auto buyer = std::make_shared<CustomerAccount>("Jan", "kowalski", "warszawa", "jan", "1234");
    system.accounts().add(buyer);

    auto vehicle = std::make_shared<Vehicle>("BMW", "M3", 3.0, 510, FuelType::Petrol, 2022, "WX12345");
    system.vehicles().add(vehicle);

    LoginUsecase loginUsecase(system.accounts());

    try {
        auto loggedUser = CustomerLoginUsecase.execute("jan", "1234");
        std::cout << "Logged in success";
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    ReserveVehicleUsecase reserveUsecase(system.vehicles());

    try {
        reserveUsecase.execute(*buyer, "WX12345");
        std::cout << "Reserveed success";
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    system.vehicles().displayAll();

}
