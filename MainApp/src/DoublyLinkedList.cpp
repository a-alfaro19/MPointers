#include "DoublyLinkedList.h"
#include <iostream>

DoublyLinkedList::DoublyLinkedList()
    : size(0) {
}

DoublyLinkedList::~DoublyLinkedList() = default;

void DoublyLinkedList::insert(const int value) {
    MPOINTER::MPointer<Node> newNode = MPOINTER::MPointer<Node>::New();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->previous = nullptr;

    if (first.isNull()) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        newNode->previous = last;
        last = newNode;
    }
    size++;
}

void DoublyLinkedList::swap(MPOINTER::MPointer<Node> a, MPOINTER::MPointer<Node> b) {
    const auto temp = a->data;
    a->data = b->data;
    b->data = temp;
}

MPOINTER::MPointer<Node> DoublyLinkedList::operator[](const int& index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    auto current = MPOINTER::MPointer<Node>::New();
    current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

int DoublyLinkedList::getSize() const {
    return size;
}

void DoublyLinkedList::printList() const {
    auto current = MPOINTER::MPointer<Node>::New();
    current = first;
    while (!current.isNull()) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
