#ifndef KOMISPO_EMPLOYEEACCOUNT_H
#define KOMISPO_EMPLOYEEACCOUNT_H

#include "Account.h"
#include "../Task/Task.h"
#include "../common/Types.h"
#include <vector>

class EmployeeAccount final : public Account {
public:
    EmployeeAccount(
        EmployeeId employeeId,
        std::string name,
        std::string surname,
        std::string login,
        const std::string& password,
        const std::vector<std::shared_ptr<Task>>& tasks
    );

    void assignTask(const std::shared_ptr<Task>& task);

    [[nodiscard]]
    const std::vector<std::shared_ptr<Task>>& getTaskList() const noexcept;

private:
    EmployeeId employeeId_;
    std::string name_;
    std::string surname_;
    std::vector<std::shared_ptr<Task>> tasks_;
};


#endif //KOMISPO_EMPLOYEEACCOUNT_H
