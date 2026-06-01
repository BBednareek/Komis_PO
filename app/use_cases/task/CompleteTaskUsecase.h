#ifndef KOMISPO_COMPLETETASKUSECASE_H
#define KOMISPO_COMPLETETASKUSECASE_H
#include "../../../domain/account/EmployeeAccount.h"
#include "../../../domain/repositories/TaskRepository.h"


class CompleteTaskUsecase final {
public:
    explicit CompleteTaskUsecase(TaskRepository& repository);

    void execute(EmployeeAccount& employee, std::size_t taskIndex) const;

private:
    TaskRepository& repository_;
};


#endif //KOMISPO_COMPLETETASKUSECASE_H
