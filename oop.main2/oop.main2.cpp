#include <iostream>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main() {

    std::cout << "---------Singly Linked List---------\n";

    SinglyLinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    list.print();

    std::cout << "Element at index 1: " << list.get(1) << std::endl;

    list.insert(1, 15);
    list.print();

    list.remove(2);
    list.print();

    std::cout << "Find 20: " << list.find(20) << std::endl;

    std::cout << "\n--------- Doubly Linked List ---------\n";

    DoublyLinkedList<int> dlist;

    dlist.push_back(1);
    dlist.push_back(2);
    dlist.push_front(0);

    dlist.print();

    return 0;
}