#ifndef KOMISPO_TASKTEMPLATE_H
#define KOMISPO_TASKTEMPLATE_H

#pragma once

#include <string>
#include <utility>

struct TaskTemplate {
    friend class TaskGenerator;

    std::string getName() {return name_;}
    std::string getDescription() {return description_;}

private:
    TaskTemplate(std::string name, std::string description) :
    name_(std::move(name)), description_(std::move(description)) {}

    std::string name_;
    std::string description_;
};

#endif //KOMISPO_TASKTEMPLATE_H
