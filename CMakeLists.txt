cmake_minimum_required(VERSION 4.2)
project(KomisPO)

set(CMAKE_CXX_STANDARD 23)

add_executable(KomisPO entrypoint/main.cpp
        domain/entities/account/Account.cpp
        domain/entities/account/Account.h
        domain/entities/account/CustomerAccount.cpp
        domain/entities/account/CustomerAccount.h
        domain/entities/account/EmployeeAccount.cpp
        domain/entities/account/EmployeeAccount.h
        domain/entities/enums/VehicleStatus.h
        domain/entities/enums/FuelType.h
        domain/entities/Vehicle/Vehicle.cpp
        domain/entities/Vehicle/Vehicle.h
        domain/entities/task/Task.cpp
        domain/entities/task/Task.h
        domain/entities/task/TaskList.cpp
        domain/entities/task/TaskList.h
)
