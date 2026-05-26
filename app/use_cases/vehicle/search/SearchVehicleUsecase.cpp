#include "SearchVehicleUsecase.h"

SearchVehicleUsecase::SearchVehicleUsecase(VehicleRepository& repository) : repository_(repository) {}

std::vector<VehicleData> SearchVehicleUsecase::execute(const VehicleSearchCriteria& criteria) const {
    return repository_.searchForCar(criteria);
}
