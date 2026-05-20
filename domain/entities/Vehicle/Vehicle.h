#ifndef KOMISPO_VEHICLE_H
#define KOMISPO_VEHICLE_H
#include <string>
#include "../enums/FuelType.h"
#include "../enums/VehicleStatus.h"

class Vehicle {
public:
    Vehicle();
    [[nodiscard]] const std::string&    getBrand()          const;
    [[nodiscard]] const std::string&    getModel()          const;
    [[nodiscard]] const std::string&    getLicensePlate()   const;
    [[nodiscard]] const FuelType&   getFuelType()   const;
    [[nodiscard]] const VehicleStatus&  getVehicleStatus()  const;
    [[nodiscard]] const double&         getEngineCapacity() const;
    [[nodiscard]] const int&            getEnginePower()    const;
    [[nodiscard]] const int&            getProductionYear() const;
    [[nodiscard]] const int&            getExpirationDate() const; // Data waznosci badania okresowego

    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setLicensePlate(const std::string& licensePlate);
    void setFuelType(const FuelType& fuelType);
    void setVehicleStatus(const VehicleStatus& vehicleStatus);
    void setEngineCapacity(const double& engineCapacity);
    void setEnginePower(const int& enginePower);
    void setProductionYear(const int& productionYear);
    void setExpirationDate(const int& expirationDate);

private:
    std::string   brand_;
    std::string   model_;
    std::string   licensePlate_;
    FuelType  fuelCategory_;
    VehicleStatus vehicleStatus_;
    double        engineCapacity_;
    int           enginePower_;
    int           productionYear_;
    int           expirationDate_;

};

#endif //KOMISPO_VEHICLE_H
