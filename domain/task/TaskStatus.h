#pragma once

#ifndef KOMISPO_TASKSTATUS_H
#define KOMISPO_TASKSTATUS_H

enum class TaskStatus {
    Pending,
    ReadyForPickup,
    Completed,
    Cancelled
};

#endif //KOMISPO_TASKSTATUS_H
