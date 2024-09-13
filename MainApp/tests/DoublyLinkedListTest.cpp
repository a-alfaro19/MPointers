#include <gtest/gtest.h>
#include "DoublyLinkedList.h"

using namespace MPOINTER;

class DoublyLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC::getInstance();
    }

    void TearDown() override {
        MPointerGC::getInstance()->stop();
    }
};

TEST_F(DoublyLinkedListTest, Insert) {
    DoublyLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0]->data, 1);
    EXPECT_EQ(list[1]->data, 2);
    EXPECT_EQ(list[2]->data, 3);
}

TEST_F(DoublyLinkedListTest, AccessByIndex) {
    DoublyLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    EXPECT_EQ(list[0]->data, 1);
    EXPECT_EQ(list[1]->data, 2);
    EXPECT_EQ(list[2]->data, 3);
}

TEST_F(DoublyLinkedListTest, PrintList) {
    DoublyLinkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    testing::internal::CaptureStdout();
    list.printList();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 \n");
}