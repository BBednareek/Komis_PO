#include "TaskRepositoryImpl.h"

#include <iostream>
#include "../../domain/common/ListTypes.h"

void TaskRepositoryImpl::add(const std::shared_ptr<Task> task)  { taskList_.pushBack(task); }

void TaskRepositoryImpl::removeCompleted()  {
    taskList_.removeIf([&](const std::shared_ptr<Task>& t) {
        return t -> getTaskStatus() == TaskStatus::Completed;
    });
}

void TaskRepositoryImpl::displayAll() const  {
    taskList_.forEach([&](const std::shared_ptr<Task>& t) {
        if (t) std::cout << *t << std::endl;
    });
}
