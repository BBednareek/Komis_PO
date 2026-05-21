#ifndef KOMISPO_EMPLOYEEACCOUNT_H
#define KOMISPO_EMPLOYEEACCOUNT_H

#include "Account.h"
#include "../Task/Task.h"
#include <vector>

class EmployeeAccount : public Account {
public:
    EmployeeAccount(
        uint32_t employeeId,
        std::string name,
        std::string surname,
        std::string
    );

    void assignTask(std::shared_ptr<Task>);

private:
    uint32_t employeeId_;
    std::string name_;
    std::vector<std::shared_ptr<Task>> tasks_;
};


#endif //KOMISPO_EMPLOYEEACCOUNT_H
