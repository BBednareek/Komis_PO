#pragma once

#ifndef KOMISPO_DOUBLYLINKEDLIST_H
#define KOMISPO_DOUBLYLINKEDLIST_H
#include <iostream>
#include <memory>

//Template uzyty dla Vehicle/TaskList - maja te same metody i strukture, stad decyzja

template<typename T>
class DoublyLinkedList final {
    struct Node final {
        std::shared_ptr<T>      data;
        std::unique_ptr<Node>   next;
        Node*                   prev {nullptr};

        explicit Node(std::shared_ptr<T> value) : data(std::move(value)) {}
    };

    std::unique_ptr<Node> head_;
    Node* tail_ {nullptr};

    void removeNode(const Node* node) {
        if (!node) return;

        if (node == head_.get()) {
            head_ = std::move(head_ -> next);

            if (head_) head_ -> prev = nullptr;
            else tail_ = nullptr;

            return;
        }

        Node* prev = node -> prev;

        if (!prev) return;

        std::unique_ptr<Node> toDelete = std::move(prev -> next);
        prev -> next = std::move(toDelete -> next);

        if (prev -> next) prev -> next -> prev = prev;
        else tail_ = prev;
    }

public:
    DoublyLinkedList()  = default;
    ~DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    void pushBack(std::shared_ptr<T> value) {
        auto newNode = std::make_unique<Node>(std::move(value));

        if (!head_) {
            tail_ = newNode.get();
            head_ = std::move(newNode);
            return;
        }

        newNode -> prev = tail_;
        tail_ -> next = std::move(newNode);
        tail_ = tail_ -> next.get();
    }

    // Dodano typnemae Predicate aby poprzednia funkcja removeCompleted mogla dzialac jako remove
    // Dla zadanej wartosci niezaleznie od rodzaju listy (Task/VehicleList)
    template<typename Predicate>
    void removeIf(Predicate pred) {
        Node* current = head_.get();

        while (current) {
            Node* next = current -> next.get();
            if (pred(current -> data)) removeNode(current);
            current = next;
        }
    }

    template<typename Func>
    void forEach(Func action) const {
        Node* current = head_.get();
        while (current) {
            action(current -> data);
            current = current -> next.get();
        }
    }

    [[nodiscard]] std::vector<std::shared_ptr<T>> getAllData() const {
        const Node* current = head_.get();
        std::vector<std::shared_ptr<T>> data;

        while (current) {
            data.emplace_back(current->data);
            current = current -> next.get();
        }

        return data;
    }

    [[nodiscard]] bool empty() const noexcept { return head_ == nullptr; }

    template<typename Predicate>
    std::shared_ptr<T> findData(Predicate pred) {
        Node* current = head_.get();

        while (current) {
            Node* next = current -> next.get();
            if (pred(current -> data)) return current -> data;
            current = next;
        }

        return nullptr;
    }
};


#endif //KOMISPO_DOUBLYLINKEDLIST_H
