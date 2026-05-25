cmake_minimum_required(VERSION 4.2)
project(KomisPO)

set(CMAKE_CXX_STANDARD 23)

add_executable(KomisPO entrypoint/main.cpp
        domain/account/Account.cpp
        domain/account/Account.h
        domain/account/CustomerAccount.cpp
        domain/account/CustomerAccount.h
        domain/account/EmployeeAccount.cpp
        domain/account/EmployeeAccount.h
        domain/Vehicle/VehicleStatus.h
        domain/Vehicle/FuelType.h
        domain/Vehicle/Vehicle.cpp
        domain/Vehicle/Vehicle.h
        domain/task/Task.cpp
        domain/task/Task.h
        domain/task/TaskStatus.h
        presentation/cli/Menu.cpp
        presentation/cli/Menu.h
        presentation/cli/ConsoleApplication.cpp
        presentation/cli/ConsoleApplication.h
        infrastructure/repositories/AccountRepositoryImpl.cpp
        infrastructure/repositories/VehicleRepositoryImpl.cpp
        infrastructure/repositories/TaskRepositoryImpl.cpp
        domain/common/ListTypes.h
        domain/common/Exceptions.h
        domain/repositories/AccountRepository.h
        domain/repositories/VehicleRepository.h
        domain/repositories/TaskRepository.h
        domain/common/DoublyLinkedList.hpp
        domain/vehicle/VehicleData.h
        domain/task/TaskData.h
        app/use_cases/auth/CustomerLoginUsecase.cpp
        app/use_cases/auth/CustomerLoginUsecase.h
        app/use_cases/auth/EmployeeLoginUsecase.cpp
        app/use_cases/auth/EmployeeLoginUsecase.h
        app/use_cases/vehicle/ReserveVehicleUsecase.cpp
        app/use_cases/vehicle/ReserveVehicleUsecase.h
        app/services/System.cpp
        app/services/System.h
        infrastructure/repositories/AccountRepositoryImpl.h
        infrastructure/repositories/TaskRepositoryImpl.h
        infrastructure/repositories/VehicleRepositoryImpl.h
)
