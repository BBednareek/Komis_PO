#pragma once

#ifndef KOMISPO_ITASKREPOSITORY_H
#define KOMISPO_ITASKREPOSITORY_H

#include <memory>
#include <vector>

class Task;

class TaskRepository {
public:
    virtual ~TaskRepository() = default;

    virtual void add(const std::shared_ptr<Task>& task) = 0;
    virtual void clear() = 0;
    [[nodiscard]] virtual std::vector<std::shared_ptr<Task>> getAllTasks() const = 0;
};


#endif //KOMISPO_ITASKREPOSITORY_H
