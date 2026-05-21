//
// Created by Mini on 21/05/2026.
//

#ifndef KOMISPO_ITASKREPOSITORY_H
#define KOMISPO_ITASKREPOSITORY_H

#include "../task/Task.h"

class ITaskRepository {
public:
    virtual ~ITaskRepository() = default;

    virtual void add(std::shared_ptr<Task> task) = 0;
    virtual void removeCompleted() = 0;
    virtual void displayAll() const = 0;

};


#endif //KOMISPO_ITASKREPOSITORY_H
