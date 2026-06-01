#include "TaskRepositoryImpl.h"

#include "../../../domain/common/ListTypes.h"

void TaskRepositoryImpl::add(const std::shared_ptr<Task>& task)  { taskList_.pushBack(task); }

[[nodiscard]] std::vector<std::shared_ptr<Task>> TaskRepositoryImpl::getAllTasks() const { return taskList_.getAllData(); }
