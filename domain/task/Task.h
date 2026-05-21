//
// Created by Mini on 20/05/2026.
//

#ifndef KOMISPO_TASK_H
#define KOMISPO_TASK_H
#include <string>

#include "../Vehicle/VehicleStatus.h"
#include "../Vehicle/Vehicle.h"

class Task {
public:
    Task();

    [[nodiscard]] const std::string& getTaskName() const;
    [[nodiscard]] const std::string& getTaskDescription() const;
    [[nodiscard]] const Vehicle& getAssignedVehicle() const;
    [[nodiscard]] const VehicleStatus& getAssignedVehicleStatus() const;

private:
    std::string taskName_;
    std::string taskDescription_;
    Vehicle assignedVehicle_;
    VehicleStatus assignedVehicleStatus_;
};


#endif //KOMISPO_TASK_H
