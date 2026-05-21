#ifndef KOMISPO_TASKLIST_H
#define KOMISPO_TASKLIST_H

#include "Task.h"

class TaskList final {
    struct Node final {
        std::shared_ptr<Task> data;
        std::unique_ptr<Node> next;
        Node* prev {nullptr};

        explicit Node(std::shared_ptr<Task> task);
    };

    void removeNode(const Node* node);
    std::unique_ptr<Node> head_;
    Node* tail_ {nullptr};

public:
    TaskList() = default;
    ~TaskList() = default;
    TaskList(const TaskList&) = delete;
    TaskList& operator=(const TaskList&) = delete;
    void pushBack(std::shared_ptr<Task> task);
    void removeCompleted();
    void display() const;
    [[nodiscard]] bool empty() const noexcept;

};


#endif //KOMISPO_TASKLIST_H
