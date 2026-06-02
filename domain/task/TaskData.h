#pragma once

#ifndef KOMISPO_TASKDATA_H
#define KOMISPO_TASKDATA_H
#include <string>
#include "TaskStatus.h"

struct TaskData final {
    std::string taskName;
    std::string description;
    std::string assignedVehicleLicensePlate;
    std::string assignedCustomerName;
    TaskStatus status {TaskStatus::Pending};
};
#endif //KOMISPO_TASKDATA_H
