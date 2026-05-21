#ifndef KOMISPO_TYPES_H
#define KOMISPO_TYPES_H

#include <cstdint>
#include "DoublyLinkedList.hpp"
#include "../../domain/task/TaskStatus.h"

using VehicleData = std::tuple<std::string, std::string, std::uint32_t, std::uint32_t, double, FuelType, VehicleStatus>;
using TaskData = std::tuple<std::string, TaskStatus>;

using TaskList = DoublyLinkedList<Task>;
using VehicleList = DoublyLinkedList<Vehicle>;

using EmployeeAccountList = DoublyLinkedList<EmployeeAccount>;
using CustomerAccountList = DoublyLinkedList<CustomerAccount>;

#endif //KOMISPO_TYPES_H
