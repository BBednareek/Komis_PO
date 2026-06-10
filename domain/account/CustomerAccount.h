#ifndef KOMISPO_CUSTOMERACCOUNT_H
#define KOMISPO_CUSTOMERACCOUNT_H
#include <memory>

#include "Account.h"
#include "../vehicle/Vehicle.h"


class CustomerAccount final : public Account {
public:
    CustomerAccount(
        std::string name,
        std::string surname,
        std::string address,
        std::string login,
        const std::string& password,
        std::uint32_t purchasedVehiclesCount
    );

    void incrementPurchasedVehicles() noexcept;
    void addReservedVehicle(const std::shared_ptr<Vehicle>& vehicle);
    [[nodiscard]] const std::string& getAddress() const noexcept;
    [[nodiscard]] std::string getFullName() const;
    [[nodiscard]] std::vector<std::shared_ptr<Vehicle>> getReservedVehicleList() const noexcept;
    [[nodiscard]] std::uint32_t getPurchasedVehiclesCount() const noexcept;
    void removeReservedVehicle(const std::string& licensePlate);


private:
    std::vector<std::shared_ptr<Vehicle>> vehicle_;
    std::string                           firstName_;
    std::string                           lastName_;
    std::string                           address_;
    std::uint32_t                         purchasedVehiclesCount_;
};


#endif //KOMISPO_CUSTOMERACCOUNT_H
