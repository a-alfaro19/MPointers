#include <gtest/gtest.h>
#include "DoublyLinkedList.h"
#include "MPointer.h"
#include "SortAlgorithms.h"

class SortAlgorithmsTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC::getInstance();
    }

    void TearDown() override {
        MPointerGC::getInstance().stop();
    }
};

TEST_F(SortAlgorithmsTest, QuickSort) {
    DoublyLinkedList<MPointer<int>> list;
    auto ptr1 = MPointer<int>::New();
    auto ptr2 = MPointer<int>::New();
    auto ptr3 = MPointer<int>::New();
    *ptr1 = 3;
    *ptr2 = 1;
    *ptr3 = 2;
    list.insert(ptr1);
    list.insert(ptr2);
    list.insert(ptr3);

    SORTALGORITHMS::quickSort(list, 0, list.getSize() - 1);

    auto it = list.begin();
    EXPECT_EQ(**it, 1);
    ++it;
    EXPECT_EQ(**it, 2);
    ++it;
    EXPECT_EQ(**it, 3);
}

TEST_F(SortAlgorithmsTest, BubbleSort) {
    DoublyLinkedList<MPointer<int>> list;
    auto ptr1 = MPointer<int>::New();
    auto ptr2 = MPointer<int>::New();
    auto ptr3 = MPointer<int>::New();
    *ptr1 = 3;
    *ptr2 = 1;
    *ptr3 = 2;
    list.insert(ptr1);
    list.insert(ptr2);
    list.insert(ptr3);

    SORTALGORITHMS::bubbleSort(list);

    auto it = list.begin();
    EXPECT_EQ(**it, 1);
    ++it;
    EXPECT_EQ(**it, 2);
    ++it;
    EXPECT_EQ(**it, 3);
}

TEST_F(SortAlgorithmsTest, InsertionSort) {
    DoublyLinkedList<MPointer<int>> list;
    auto ptr1 = MPointer<int>::New();
    auto ptr2 = MPointer<int>::New();
    auto ptr3 = MPointer<int>::New();
    *ptr1 = 3;
    *ptr2 = 1;
    *ptr3 = 2;
    list.insert(ptr1);
    list.insert(ptr2);
    list.insert(ptr3);

    SORTALGORITHMS::insertionSort(list);

    auto it = list.begin();
    EXPECT_EQ(**it, 1);
    ++it;
    EXPECT_EQ(**it, 2);
    ++it;
    EXPECT_EQ(**it, 3);
}