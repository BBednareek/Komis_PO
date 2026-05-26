#pragma once

#ifndef KOMISPO_TASKGENERATOR_H
#define KOMISPO_TASKGENERATOR_H
#include "TaskTemplate.h"

class TaskGenerator {
public:

    static TaskTemplate generateReservationTask(
        const std::string& customerName
    );
};


#endif //KOMISPO_TASKGENERATOR_H
