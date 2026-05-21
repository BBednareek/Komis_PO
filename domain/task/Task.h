#ifndef KOMISPO_TASK_H
#define KOMISPO_TASK_H
#include <memory>
#include <string>
#include "../Vehicle/Vehicle.h"
#include "TaskStatus.h"

class Task {
public:
    Task(std::string taskName, std::string description, const std::shared_ptr<Vehicle>& vehicle, TaskStatus status);

    [[nodiscard]] const std::string&            getTaskName()        const;
    [[nodiscard]] const std::string&            getTaskDescription() const;
    [[nodiscard]] const std::weak_ptr<Vehicle>& getAssignedVehicle() const;
    [[nodiscard]] const TaskStatus&             getTaskStatus()      const;

    void complete();

private:
    std::string taskName_;
    std::string taskDescription_;
    std::weak_ptr<Vehicle> vehicle_;
    TaskStatus status_ { TaskStatus::Pending };

};


#endif //KOMISPO_TASK_H
