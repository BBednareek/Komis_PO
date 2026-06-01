#include "TaskRepositoryImpl.h"

#include "../../../domain/common/ListTypes.h"

void TaskRepositoryImpl::add(const std::shared_ptr<Task>& task)  { taskList_.pushBack(task); }

void TaskRepositoryImpl::clear() {
    taskList_.clear();
}

[[nodiscard]] std::vector<std::shared_ptr<Task>> TaskRepositoryImpl::getAllTasks() const { return taskList_.getAllData(); }
