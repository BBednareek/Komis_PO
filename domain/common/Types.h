#ifndef KOMISPO_TYPES_H
#define KOMISPO_TYPES_H

#include <cstdint>
#include "DoublyLinkedList.hpp"

class Task;
class Vehicle;

using VehicleData = std::tuple<std::string, std::string, std::uint32_t, std::uint32_t, double, FuelType>;
using TaskList = DoublyLinkedList<Task>;
using VehicleList = DoublyLinkedList<Vehicle>;

#endif //KOMISPO_TYPES_H
