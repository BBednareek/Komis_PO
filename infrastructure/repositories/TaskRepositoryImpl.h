#ifndef KOMISPO_TASKREPOSITORYIMPL_H
#define KOMISPO_TASKREPOSITORYIMPL_H

#include "../../domain/repositories/TaskRepository.h"
#include <iostream>
#include "../../domain/common/ListTypes.h"

class TaskRepositoryImpl final : public TaskRepository {
public:
    void add(std::shared_ptr<Task> task) override;
    void removeCompleted() override;
    void displayAll() const override;

private:
    TaskList taskList_;
};

#endif //KOMISPO_TASKREPOSITORYIMPL_H
