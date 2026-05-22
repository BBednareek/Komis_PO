#pragma once

#ifndef KOMISPO_TASKDATA_H
#define KOMISPO_TASKDATA_H
#include <string>
#include <tuple>
#include "TaskStatus.h"

using TaskData = std::tuple<std::string, TaskStatus>;

#endif //KOMISPO_TASKDATA_H
