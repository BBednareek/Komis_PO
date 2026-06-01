#ifndef KOMISPO_VEHICLESEARCHCRITERIA_H
#define KOMISPO_VEHICLESEARCHCRITERIA_H
#include <optional>
#include <string>

#include "FuelType.h"

struct VehicleSearchCriteria {
    std::optional<std::string> brand;
    std::optional<std::string> model;
    std::optional<std::uint32_t> minYear;
    std::optional<std::uint32_t> maxYear;
    std::optional<double> engineCapacity;
    std::optional<FuelType> fuelType;
};

#endif //KOMISPO_VEHICLESEARCHCRITERIA_H
