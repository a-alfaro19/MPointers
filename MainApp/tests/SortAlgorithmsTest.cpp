#include <gtest/gtest.h>
#include "DoublyLinkedList.h"
#include "MPointer.h"
#include "SortAlgorithms.h"
#include <random>

class SortAlgorithmsTest : public ::testing::Test {};

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

TEST_F(SortAlgorithmsTest, QuickSort) {
    DoublyLinkedList* list = createRandomList(10, 20);
    SORTALGORITHMS::quickSort(*list, 0, list->getSize() - 1);

    for (int i = 0; i < list->getSize() - 1; i++) {
        ASSERT_LE((*list)[i]->data, (*list)[i + 1]->data);
    }
}

TEST_F(SortAlgorithmsTest, BubbleSort) {
    const DoublyLinkedList* list = createRandomList(10, 20);
    SORTALGORITHMS::bubbleSort(*list);

    for (int i = 0; i < list->getSize() - 1; i++) {
        ASSERT_LE((*list)[i]->data, (*list)[i + 1]->data);
    }
}

TEST_F(SortAlgorithmsTest, InsertionSort) {
    const DoublyLinkedList* list = createRandomList(10, 20);
    SORTALGORITHMS::insertionSort(*list);

    for (int i = 0; i < list->getSize() - 1; i++) {
        ASSERT_LE((*list)[i]->data, (*list)[i + 1]->data);
    }
}