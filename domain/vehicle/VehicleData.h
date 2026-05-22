#pragma once

#ifndef KOMISPO_VEHICLEDATA_H
#define KOMISPO_VEHICLEDATA_H
#include <string>
#include <tuple>
#include "FuelType.h"
#include "VehicleStatus.h"

using VehicleData = std::tuple<
    std::string,
    std::string,
    std::uint32_t,
    std::uint32_t,
    double,
    FuelType,
    VehicleStatus
>;

#endif //KOMISPO_VEHICLEDATA_H
