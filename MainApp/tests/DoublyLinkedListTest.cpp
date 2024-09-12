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
    EXPECT_EQ(list[0]->value, 1);
    EXPECT_EQ(list[1]->value, 2);
    EXPECT_EQ(list[2]->value, 3);
}

