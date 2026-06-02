#include "VehicleRepositoryImpl.h"

#include <algorithm>
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
void VehicleRepositoryImpl::remove(const std::string_view registration) {
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

std::vector<VehicleData>
VehicleRepositoryImpl::searchForCar(const VehicleSearchCriteria& criteria) {
    std::vector<VehicleData> results;

    auto normalize = [](std::string value) {
        // ReSharper disable once CppUseRangeAlgorithm
        std::transform(value.begin(), value.end(), value.begin(), [](const unsigned char c) {
            return static_cast<char>(std::toupper(c));
        });

        return value;
    };

    vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
        if (v == nullptr) return;

        const VehicleData vData = v->getVehicleData();

        if (criteria.brand.has_value()) {
            const auto vehicleBrand = normalize(vData.brand);

            if (const auto searchBrand = normalize(criteria.brand.value()); vehicleBrand.find(searchBrand) == std::string::npos) {
                return;
            }
        }

        if (criteria.model.has_value()) {
            const auto vehicleModel = normalize(vData.model);

            if (const auto searchModel = normalize(criteria.model.value()); vehicleModel.find(searchModel) == std::string::npos) {
                return;
            }
        }

        if (criteria.minYear.has_value() &&
            vData.productionYear < criteria.minYear.value()) {
            return;
        }

        if (criteria.maxYear.has_value() &&
            vData.productionYear > criteria.maxYear.value()) {
            return;
        }

        if (criteria.fuelType.has_value() &&
            vData.fuelType != criteria.fuelType.value()) {
            return;
        }

        results.push_back(vData);
    });

    return results;
}
