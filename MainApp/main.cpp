#include <DoublyLinkedList.h>
#include <iostream>
#include <SortAlgorithms.h>
#include "MPointer.h"
#include <random>
#include <unistd.h>

using namespace MPOINTER;

DoublyLinkedList* createRandomList(const int size, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max);
    auto* list = new DoublyLinkedList();
    for (int i = 0; i < size; i++) {
        list->insert(dis(gen));
    }
    return list;
}

int main()
{
    DoublyLinkedList* list = createRandomList(10, 20);
    std::cout << "Finish creating list" << std::endl;
    list->printList();
    std::cout << "Finish printing list" << std::endl;
    SORTALGORITHMS::insertionSort(*list);
    list->printList();
    std::cout << list->getSize() << std::endl;
    return 0;
}
