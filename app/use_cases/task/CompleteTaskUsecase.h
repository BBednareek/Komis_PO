#ifndef KOMISPO_COMPLETETASKUSECASE_H
#define KOMISPO_COMPLETETASKUSECASE_H
#include "../../../domain/account/EmployeeAccount.h"


class CompleteTaskUsecase final {
public:
    CompleteTaskUsecase() = default;

    void execute(EmployeeAccount& employee, std::size_t taskIndex) const;
};


#endif //KOMISPO_COMPLETETASKUSECASE_H
