#include "VehicleRepositoryImpl.h"

#include <iostream>
#include <memory>
#include <vector>
#include "../../../domain/common/Exceptions.h"
#include "../../../domain/repositories/VehicleRepository.h"
#include "../../../domain/common/ListTypes.h"

void VehicleRepositoryImpl::add(const std::shared_ptr<Vehicle> vehicle) {
        if (vehicle == nullptr) throw ValidationException("Nie mozna dodac pustego pojadzu");

        const auto existingVehicle = vehicleList_.findData([&](const std::shared_ptr<Vehicle>& candidate) {
            return candidate != nullptr && candidate -> getLicensePlate() == vehicle->getLicensePlate();
        });

        if (existingVehicle != nullptr) throw ValidationException("Pojazd wystepuje juz w bazie");

        vehicleList_.pushBack(vehicle);
    }

    // Ze wzgledu na predykat uzyty w template nalezalo wykorzystac lambda functions do porownania
    void VehicleRepositoryImpl::remove(const std::string_view registration)  {
        static_cast<void>(findByRegistration(registration));

        vehicleList_.removeIf([&](const std::shared_ptr<Vehicle>& v) {
            return v -> getLicensePlate() == registration;
        });
    }

    std::shared_ptr<Vehicle> VehicleRepositoryImpl::findByRegistration(const std::string_view registration)  {
        const auto vehiclePtr = vehicleList_.findData([&](const std::shared_ptr<Vehicle>& v) {
            return v -> getLicensePlate() == registration;
        });

        if (vehiclePtr) return vehiclePtr;
        throw VehicleException("Nie znaleziono pojazdu");
    }

    std::vector<VehicleData> VehicleRepositoryImpl::getAllVehicles() const {
        std::vector<VehicleData> data;
        vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
            if (v) data.push_back(v -> getVehicleData());
        });

        return data;
    }

    void VehicleRepositoryImpl::displayAllVehicles() const {
        vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
            if (v) std::cout << *v << std::endl;
        });
    }
