//
// Created by Mini on 21/05/2026.
//

#include "../../domain/repositories/ITaskRepository.h"


class IMTaskRepository final : public ITaskRepository {
public:
    void add(const std::shared_ptr<Task> task) override { taskList_.pushBack(task); }
    void removeCompleted() override {
        taskList_.removeIf([&](const std::shared_ptr<Task>& t) {
           return t -> getTaskStatus() == TaskStatus::Completed;
        });
    }

    void displayAll() const override {
        taskList_.forEach([&](const std::shared_ptr<Task>& t) {
           if (t) std::cout << *t << std::endl;
        });
    }
private:
    TaskList taskList_;
};