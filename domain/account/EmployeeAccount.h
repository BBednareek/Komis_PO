#ifndef KOMISPO_EMPLOYEEACCOUNT_H
#define KOMISPO_EMPLOYEEACCOUNT_H

#include "Account.h"
#include "../task/Task.h"
#include <string_view>
#include <vector>

class EmployeeAccount final : public Account {
public:
    EmployeeAccount(
        std::string name,
        std::string surname,
        std::string login,
        const std::string& password,
        const std::vector<std::shared_ptr<Task>>& tasks
    );

    void assignTask(const std::shared_ptr<Task>& task);
    void completeTask(std::size_t index);
    void completeTasksForVehicle(std::string_view licensePlate) const;

    [[nodiscard]] std::string getFullName() const noexcept;
    [[nodiscard]] std::uint32_t getPendingTaskCount() const noexcept;
    [[nodiscard]] const std::vector<std::shared_ptr<Task>>& getTaskList() const noexcept;


private:
    std::string name_;
    std::string surname_;
    std::vector<std::shared_ptr<Task>> tasks_;
};

#endif //KOMISPO_EMPLOYEEACCOUNT_H
