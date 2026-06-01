#include "CompleteTaskUsecase.h"


void CompleteTaskUsecase::execute(EmployeeAccount& employee, const std::size_t taskIndex) const {
    employee.completeTask(taskIndex);
}
