#pragma once

#ifndef KOMISPO_TASK_H
#define KOMISPO_TASK_H

#include <memory>
#include <string>

#include "TaskData.h"
#include "TaskStatus.h"

class CustomerAccount;
class Vehicle;

class Task {
public:
    Task(
        std::string taskName,
        std::string description,
        const std::shared_ptr<Vehicle>& vehicle,
        const std::shared_ptr<CustomerAccount>& customer,
        TaskStatus status
    );

    [[nodiscard]] const std::string& getTaskName() const;
    [[nodiscard]] const std::string& getTaskDescription() const;
    [[nodiscard]] const std::weak_ptr<CustomerAccount>& getAssignedCustomer() const;
    [[nodiscard]] const std::string& getAssignedVehicleLicensePlate() const;
    [[nodiscard]] const std::string& getAssignedCustomerName() const;
    [[nodiscard]] const TaskStatus& getTaskStatus() const;

    void markReadyForPickup();
    void complete();
    void cancel();

private:
    std::string taskName_;
    std::string taskDescription_;
    std::weak_ptr<Vehicle> vehicle_;
    std::weak_ptr<CustomerAccount> customer_;
    std::string assignedVehicleLicensePlate_;
    std::string assignedCustomerName_;
    TaskStatus status_ { TaskStatus::Pending };
};

#endif //KOMISPO_TASK_H
