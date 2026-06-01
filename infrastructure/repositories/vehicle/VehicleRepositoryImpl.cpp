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

    void VehicleRepositoryImpl::displayAllVehicles() const {
        vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
            if (v) std::cout << *v << std::endl;
        });
    }

std::vector<VehicleData>
VehicleRepositoryImpl::searchForCar(const VehicleSearchCriteria& criteria) {
    std::vector<VehicleData> results;

    vehicleList_.forEach([&](const std::shared_ptr<Vehicle>& v) {
        if (v == nullptr) return;

        const VehicleData vData = v->getVehicleData();

        // customowy to_upper, zaimplementowany z powodu problemow z wywolaniem wbudowanej funkcji
        auto to_upper = [](const unsigned char c) { return std::toupper(c); };

        std::optional<std::string> searchBrand = criteria.brand;
        std::optional<std::string> searchModel = criteria.model;

        // Resharper z CLion zeby usunac informacje o mozliwosci skorzystania z std::ranges::transform()
        // ReSharper disable all CppUseRangeAlgorithm
        if (searchBrand) std::transform(searchBrand->begin(), searchBrand->end(), searchBrand->begin(),  to_upper);
        if (searchModel) std::transform(searchModel->begin(), searchModel->end(), searchModel->begin(),  to_upper);

        std::string brand = vData.brand;
        std::string model = vData.model;

        std::transform(brand.begin(), brand.end(), brand.begin(), to_upper);
        std::transform(model.begin(), model.end(), model.begin(), to_upper);

        //*.find daje mozliwosc partial match
        // przydaje sie to gdy uzytkownik omylkowo wprowadzi np "BM" zamiast "BMW"
        if (searchBrand.has_value() &&
            brand.find(searchBrand.value()) == std::string::npos) return;

        if (searchModel.has_value() &&
            model.find(searchModel.value()) == std::string::npos) return;


        if (criteria.minYear.has_value() &&
            vData.productionYear < criteria.minYear.value()) return;


        if (criteria.maxYear.has_value() &&
            vData.productionYear > criteria.maxYear.value()) return;


        if (criteria.fuelType.has_value() &&
            vData.fuelType != criteria.fuelType.value()) return;


        results.push_back(vData);
    });

    return results;
}

