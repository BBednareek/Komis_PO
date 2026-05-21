#ifndef KOMISPO_VEHICLE_H
#define KOMISPO_VEHICLE_H
#include <string>
#include "FuelType.h"
#include "VehicleStatus.h"

class Vehicle {
public:
    Vehicle(std::string brand,
        std::string model,
        double engineCapacity,
        std::uint32_t horsePower,
        FuelType fuelType,
        std::uint32_t productionYear,
        std::string registrationNumber
        );

    [[nodiscard]] const std::string&    getBrand()          const;
    [[nodiscard]] const std::string&    getModel()          const;
    [[nodiscard]] const std::string&    getLicensePlate()   const;
    [[nodiscard]] const FuelType&   getFuelType()   const;
    [[nodiscard]] const VehicleStatus&  getVehicleStatus()  const;
    [[nodiscard]] const double&         getEngineCapacity() const;
    [[nodiscard]] const int&            getHorsePower()    const;
    [[nodiscard]] const int&            getProductionYear() const;
    [[nodiscard]] const int&            getExpirationDate() const; // Data waznosci badania okresowego

    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setLicensePlate(const std::string& licensePlate);
    void setFuelType(const FuelType& fuelType);
    void setVehicleStatus(const VehicleStatus& vehicleStatus);
    void setEngineCapacity(const double& engineCapacity);
    void setHorsePower(const int& enginePower);
    void setProductionYear(const int& productionYear);
    void setExpirationDate(const int& expirationDate);

    void reserve();
    void markReadyForPickup();
    void release();

private:
    std::string   brand_;
    std::string   model_;
    std::string   licensePlate_;
    FuelType      fuelCategory_;
    VehicleStatus vehicleStatus_ { VehicleStatus::ForSale };
    std::uint32_t horsePower_;
    double        engineCapacity_;
    int           productionYear_;
    int           expirationDate_;

};

#endif //KOMISPO_VEHICLE_H
