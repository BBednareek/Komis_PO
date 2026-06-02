#ifndef KOMISPO_TASKREPOSITORYIMPL_H
#define KOMISPO_TASKREPOSITORYIMPL_H

#include "../../../domain/repositories/TaskRepository.h"
#include "../../../domain/common/ListTypes.h"



class TaskRepositoryImpl : public TaskRepository {
public:
    void add(const std::shared_ptr<Task>& task) override;
    [[nodiscard]] std::vector<std::shared_ptr<Task>> getAllTasks() const override;

private:
    TaskList taskList_;
};

#endif //KOMISPO_TASKREPOSITORYIMPL_H
