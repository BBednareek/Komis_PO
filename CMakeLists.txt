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
        domain/task/TaskList.cpp
        domain/task/TaskList.h
        domain/task/TaskStatus.h
        presentation/cli/Menu.cpp
        presentation/cli/Menu.h
        presentation/cli/ConsoleApplication.cpp
        presentation/cli/ConsoleApplication.h
        infrastructure/repositories/IMAccountRepository.cpp
        infrastructure/repositories/IMAccountRepository.h
        infrastructure/repositories/IMVehicleRepository.cpp
        infrastructure/repositories/IMVehicleRepository.h
        infrastructure/repositories/IMTaskRepository.cpp
        infrastructure/repositories/IMTaskRepository.h
        domain/common/Types.h
        domain/common/Exceptions.h
        domain/repositories/IAccountRepository.h
        domain/repositories/IVehicleRepository.h
        domain/repositories/ITaskRepository.h
)
