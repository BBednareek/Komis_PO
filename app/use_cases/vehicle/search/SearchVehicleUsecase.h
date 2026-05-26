//
// Created by Mini on 26/05/2026.
//

#ifndef KOMISPO_SEARCHVEHICLEUSECASE_H
#define KOMISPO_SEARCHVEHICLEUSECASE_H
#include "../../../../domain/repositories/VehicleRepository.h"


class SearchVehicleUsecase final {
public:
    explicit SearchVehicleUsecase(VehicleRepository& repository);

    [[nodiscard]] std::vector<VehicleData> execute(const VehicleSearchCriteria& criteria) const;

private:
    VehicleRepository& repository_;
};


#endif //KOMISPO_SEARCHVEHICLEUSECASE_H
