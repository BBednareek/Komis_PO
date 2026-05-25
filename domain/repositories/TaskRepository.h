#pragma once

#ifndef KOMISPO_ITASKREPOSITORY_H
#define KOMISPO_ITASKREPOSITORY_H

#include "../task/Task.h"

class TaskRepository {
public:
    virtual ~TaskRepository() = default;

    virtual void add(std::shared_ptr<Task> task) = 0;
    virtual void removeCompleted() = 0;
    virtual void displayAll() const = 0;

};


#endif //KOMISPO_ITASKREPOSITORY_H
