#include <MPointerList.h>
#include <iostream>

using namespace MPOINTER;

MPointerList::MPointerList() noexcept: head(nullptr), tail(nullptr), size(0) {}

MPointerList::~MPointerList() noexcept {
    const Node* current = head;

    while (current) {
        const Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void MPointerList::insert(const PointerInfo& data) {
    auto* newNode = new Node{data, nullptr, nullptr};

    if(!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    size++;
}

int MPointerList::getSize() const {
    return size;
}

void MPointerList::removeUnusedPointers() {
    const Node* current = head;
    while (current) {
        if (current->data.refCount == 0 &&
            current->data.pointer == nullptr) { // If the reference count is 0 and the pointer is null, remove the node
            const Node* temp = current->next;
            if (current->previous) {
                current->previous->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->previous = current->previous;
            } else {
                tail = current->previous;
            }
            delete current;
            current = temp;
            size--;
        } else {
            current = current->next;
        }
    }
}

PointerInfo* MPointerList::find(const int id) const {
    Node* current = head;

    while (current) {
        if (current->data.id == id) {
            return &current->data;
        }
        current = current->next;
    }

    return nullptr;
}

void MPointerList::clear() {
    const Node* current = head;
    while (current) {
        const Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

void MPointerList::printList() const {
    const Node* current = head;
    while (current) {
        std::cout << "ID: " << current->data.id << " RefCount: " << current->data.refCount << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}
