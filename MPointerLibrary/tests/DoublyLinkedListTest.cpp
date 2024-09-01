#include <gtest/gtest.h>
#include <DoublyLinkedList.h>
#include <MPointer.h>

class DoublyLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC::getInstance();
    }

    void TearDown() override {
        MPointerGC::getInstance()->stop();
    }
};

TEST_F(DoublyLinkedListTest, InsertTest) {
    DoublyLinkedList<MPointer<int>> list;
    MPointer<int> mPointer = MPointer<int>::New();
    *mPointer = 1;
    MPointer<int> mPointer2 = MPointer<int>::New();
    *mPointer2 = 2;
    MPointer<int> mPointer3 = MPointer<int>::New();
    *mPointer3 = 3;

    list.insert(mPointer);
    list.insert(mPointer2);
    list.insert(mPointer3);

    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(*list[0], 1);
    EXPECT_EQ(*list[1], 2);
    EXPECT_EQ(*list[2], 3);
}

TEST_F(DoublyLinkedListTest, RemoveTest) {
    DoublyLinkedList<MPointer<int>> list;
    MPointer<int> mPointer = MPointer<int>::New();
    *mPointer = 1;
    MPointer<int> mPointer2 = MPointer<int>::New();
    *mPointer2 = 2;
    MPointer<int> mPointer3 = MPointer<int>::New();
    *mPointer3 = 3;

    list.insert(mPointer);
    list.insert(mPointer2);
    list.insert(mPointer3);
    list.remove(mPointer2);

    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(*list[0], 1);
    EXPECT_EQ(*list[1], 3);
}

TEST_F(DoublyLinkedListTest, SwapTest) {
    DoublyLinkedList<MPointer<int>> list;
    MPointer<int> mPointer = MPointer<int>::New();
    *mPointer = 1;
    MPointer<int> mPointer2 = MPointer<int>::New();
    *mPointer2 = 2;
    MPointer<int> mPointer3 = MPointer<int>::New();
    *mPointer3 = 3;

    list.insert(mPointer);
    list.insert(mPointer2);
    list.insert(mPointer3);

    list.swap(mPointer, mPointer3);
    EXPECT_EQ(*list[0], 3);
    EXPECT_EQ(*list[2], 1);
}

TEST_F(DoublyLinkedListTest, GetSizeTest) {
    DoublyLinkedList<MPointer<int>> list;
    EXPECT_EQ(list.getSize(), 0);

    MPointer<int> mPointer = MPointer<int>::New();
    *mPointer = 1;

    list.insert(mPointer);
    EXPECT_EQ(list.getSize(), 1);
}

TEST_F(DoublyLinkedListTest, IteratorTest) {
    DoublyLinkedList<MPointer<int>> list;
    MPointer<int> mPointer = MPointer<int>::New();
    *mPointer = 1;
    MPointer<int> mPointer2 = MPointer<int>::New();
    *mPointer2 = 2;
    MPointer<int> mPointer3 = MPointer<int>::New();
    *mPointer3 = 3;

    list.insert(mPointer);
    list.insert(mPointer2);
    list.insert(mPointer3);

    auto it = list.begin();
    EXPECT_EQ(**it, 1);
    ++it;
    EXPECT_EQ(**it, 2);
    ++it;
    EXPECT_EQ(**it, 3);
    ++it;
    EXPECT_EQ(it, list.end());
}