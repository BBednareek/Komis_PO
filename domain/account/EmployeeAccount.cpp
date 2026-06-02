#include "EmployeeAccount.h"

#include "../common/Exceptions.h"

EmployeeAccount::EmployeeAccount(
        const std::uint32_t employeeId,
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
        if (task == nullptr) throw TaskException("Nie mozna przypisac pustego zadania");

        tasks_.push_back(task);
}

void EmployeeAccount::completeTask(const std::size_t index) {
        if (index >= tasks_.size() || tasks_[index] == nullptr) throw TaskException("Nie znaleziono zadania o podanym indeksie");

        tasks_[index]->complete();
}

void EmployeeAccount::completeTasksForVehicle(const std::string_view licensePlate) const {
        for (const auto& task : tasks_) {
                if (task == nullptr) continue;

                if (task->getAssignedVehicleLicensePlate() != licensePlate) continue;
                if (task->getTaskStatus() == TaskStatus::Completed || task->getTaskStatus() == TaskStatus::Cancelled) continue;

                task->cancel();
        }
}

[[nodiscard]] std::uint32_t EmployeeAccount::getEmployeeId() const noexcept { return employeeId_; }
[[nodiscard]] std::string EmployeeAccount::getFullName() const noexcept { return name_ + ' ' + surname_; }
[[nodiscard]] std::uint32_t EmployeeAccount::getPendingTaskCount() const noexcept {
        std::uint32_t pendingTask {0};
        for (const auto& task : tasks_)
                if (task != nullptr && task -> getTaskStatus() == TaskStatus::Pending)
                        ++pendingTask;
        return pendingTask;
}

[[nodiscard]]
const std::vector<std::shared_ptr<Task>>& EmployeeAccount::getTaskList() const noexcept {
        return tasks_;
}
