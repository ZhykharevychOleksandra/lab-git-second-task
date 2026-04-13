#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Node.h"

template <typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    int size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    // додати на початок
    void push_front(T value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // додати в кінець
    void push_back(T value) {
        auto newNode = std::make_shared<Node<T>>(value);

        if (!head) {
            head = newNode;
        }
        else {
            auto temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    // видалити перший
    void pop_front() {
        if (!head)
            throw std::runtime_error("List is empty");

        head = head->next;
        size--;
    }

    // видалити останній
    void pop_back() {
        if (!head)
            throw std::runtime_error("List is empty");

        if (!head->next) {
            head = nullptr;
        }
        else {
            auto temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            temp->next = nullptr;
        }
        size--;
    }

    // доступ по індексу
    T get(int index) const {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        auto temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // вставка по індексу
    void insert(int index, T value) {
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");

        if (index == 0) {
            push_front(value);
            return;
        }

        auto newNode = std::make_shared<Node<T>>(value);
        auto temp = head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    // видалення по індексу
    void remove(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        if (index == 0) {
            pop_front();
            return;
        }

        auto temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        temp->next = temp->next->next;
        size--;
    }

    // розмір
    int getSize() const {
        return size;
    }

    // перевірка чи пустий
    bool isEmpty() const {
        return size == 0;
    }

    // пошук
    int find(T value) const {
        auto temp = head;
        int index = 0;

        while (temp) {
            if (temp->data == value)
                return index;
            temp = temp->next;
            index++;
        }

        return -1;
    }

    // вивід
    void print() const {
        auto temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "null\n";
    }
};