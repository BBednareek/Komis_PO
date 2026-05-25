#include "CompleteTaskUsecase.h"


CompleteTaskUsecase::CompleteTaskUsecase(TaskRepository& repository) : repository_(repository) {}

void CompleteTaskUsecase::execute(const EmployeeAccount& employee, const std::size_t taskIndex) const {
    employee.completeTask(taskIndex);
    static_cast<void>(repository_);
}