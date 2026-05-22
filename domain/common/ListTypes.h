#pragma once

#ifndef KOMISPO_TYPES_H
#define KOMISPO_TYPES_H

#include <cstdint>
#include "DoublyLinkedList.hpp"
#include "../../domain/account/CustomerAccount.h"
#include "../../domain/account/EmployeeAccount.h"


using TaskList = DoublyLinkedList<Task>;
using VehicleList = DoublyLinkedList<Vehicle>;

using EmployeeAccountList = DoublyLinkedList<EmployeeAccount>;
using CustomerAccountList = DoublyLinkedList<CustomerAccount>;

#endif //KOMISPO_TYPES_H
