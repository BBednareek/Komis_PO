#include <iostream>
#include <memory>
#include <vector>
#include "../../domain/common/Exceptions.h"
#include "../../domain/repositories/IVehicleRepository.h"
#include "../../domain/common/ListTypes.h"

class IMVehicleRepository final : public IVehicleRepository {
public:
    void add(const std::shared_ptr<Vehicle> vehicle) override { vehicleList_.pushBack(vehicle); }

    // Ze wzgledu na predykat uzyty w template nalezalo wykorzystac lambda functions do porownania
    void remove(const std::string_view registration) override {
        vehicleList_.removeIf([&](const std::shared_ptr<Vehicle>& v) {
            return v -> getLicensePlate() == registration;
        });
    }

    VehicleData findByRegistration(const std::string_view registration) override {
        const auto vehiclePtr = vehicleList_.findData([&](const std::shared_ptr<Vehicle>& v) {
            return v -> getLicensePlate() == registration;
        });

        if (vehiclePtr) return vehiclePtr -> getVehicleData();
        throw VehicleException("Nie znaleziono pojazdu");
    }

    std::vector<VehicleData> getAllVehicles() override {
        std::vector<VehicleData> data;

        vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
            if (v) data.push_back(v -> getVehicleData());
        });

        return data;
    }

    void displayAllVehicles() const override {
        vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
            if (v) std::cout << *v << std::endl;
        });
    }


private:
    VehicleList vehicleList_;
};
