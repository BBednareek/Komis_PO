#ifndef KOMISPO_EMPLOYEEACCOUNT_H
#define KOMISPO_EMPLOYEEACCOUNT_H

#include "Account.h"
#include "../Task/Task.h"
#include <vector>

class EmployeeAccount final : public Account {
public:
    EmployeeAccount(
        std::uint32_t employeeId,
        std::string name,
        std::string surname,
        std::string login,
        const std::string& password,
        const std::vector<std::shared_ptr<Task>>& tasks
    );

    void assignTask(const std::shared_ptr<Task>& task);
    void completeTask(std::size_t index) const;

    [[nodiscard]] std::uint32_t getEmployeeId() const noexcept;
    [[nodiscard]] const std::string& getFirstName() const noexcept;
    [[nodiscard]] const std::string& getLastName() const noexcept;
    [[nodiscard]] std::string getFullName() const noexcept;
    [[nodiscard]] std::uint32_t getPendingTaskCount() const noexcept;
    [[nodiscard]] const std::vector<std::shared_ptr<Task>>& getTaskList() const noexcept;


private:
    std::uint32_t employeeId_;
    std::string name_;
    std::string surname_;
    std::vector<std::shared_ptr<Task>> tasks_;
};

#endif //KOMISPO_EMPLOYEEACCOUNT_H
