//
// Created by Mini on 20/05/2026.
//

#include "EmployeeAccount.h"

EmployeeAccount::EmployeeAccount(
        const EmployeeId employeeId,
        std::string name,
        std::string surname,
        std::string login,
        const std::string& password,
        const std::vector<std::shared_ptr<Task>>& tasks
        ) : Account(std::move(login), password),
        employeeId_(employeeId),
        name_(std::move(name)),
        surname_(std::move(surname)),
        tasks_(tasks) {}

void EmployeeAccount::assignTask(const std::shared_ptr<Task>& task) {
        tasks_.push_back(task);
}

[[nodiscard]]
const std::vector<std::shared_ptr<Task>>& EmployeeAccount::getTaskList() const noexcept {
        return tasks_;
}