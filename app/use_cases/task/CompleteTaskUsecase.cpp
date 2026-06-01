#include "CompleteTaskUsecase.h"


CompleteTaskUsecase::CompleteTaskUsecase(TaskRepository& repository) : repository_(repository) {}

void CompleteTaskUsecase::execute(EmployeeAccount& employee, const std::size_t taskIndex) const {
    employee.completeTask(taskIndex);
    repository_.removeCompleted();
}
