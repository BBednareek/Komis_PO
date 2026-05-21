#include "TaskList.h"
#include <iostream>

TaskList::Node::Node(std::shared_ptr<Task> task) : data(std::move(task)) {}

void TaskList::removeNode(const Node* node) {
    if (!node) return;

    if (node == head_.get()) {
        head_ = std::move(head_ -> next);

        if (head_) head_ -> prev = nullptr;
        else tail_ = nullptr;

        return;
    }

    auto* previous = node -> prev;
    const auto removed = std::move(previous -> next);

    previous -> next = std::move(removed -> next);

    if (previous -> next) previous -> next -> prev = previous;
    else tail_ = previous;
}

void TaskList::pushBack(std::shared_ptr<Task> task) {
    auto newNode = std::make_unique<Node>(std::move(task));

    if (!head_) {
        // ReSharper disable once CppDFALocalValueEscapesFunction
        // newNode jest unique_ptr ale nie przechowuje nigdzie adresu newNode
        //newNode.get() zwraca adres dynamic allocated node'a na heapie nie na stacku
        // false positive ostrzezenie
        tail_ = newNode.get();
        head_ = std::move(newNode);

        return;
    }

    newNode -> prev = tail_;
    tail_ -> next = std::move(newNode);
    tail_ = tail_ -> next.get();
}

void TaskList::removeCompleted() {
    const Node* current = head_.get();

    while (current) {
        if (current -> data -> getTaskStatus() == TaskStatus::Completed) {
            removeNode(current);
            break;
        }

        current = current -> next.get();
    }
}

void TaskList::display() const {
    const Node* current = head_.get();

    while (current) {
        std::cout << current -> data -> getTaskDescription() << '\n';
        current = current -> next.get();
    }
}

[[nodiscard]] bool TaskList::empty() const noexcept { return head_ == nullptr; }