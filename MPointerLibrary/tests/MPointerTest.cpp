#include <gtest/gtest.h>
#include "MPointer.h"

using namespace MPOINTER;

class MPointerTest : public ::testing::Test {};

TEST_F(MPointerTest, CreateAndAssignValue) {
    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;
    EXPECT_EQ(*myPtr, 5);
}

TEST_F(MPointerTest, PointerAssignment) {
    MPointer<int> myPtr = MPointer<int>::New();
    MPointer<int> myPtr2 = MPointer<int>::New();

    *myPtr = 10;
    myPtr2 = myPtr;

    EXPECT_EQ(*myPtr2, 10);
}

TEST_F(MPointerTest, DereferenceOperator) {
    auto mPointer = MPointer<int>::New();
    *mPointer = 10;
    EXPECT_EQ(*mPointer, 10);
}

TEST_F(MPointerTest, AssignmentOperator) {
    auto mPointer1 = MPointer<int>::New();
    *mPointer1 = 10;
    auto mPointer2 = MPointer<int>::New();
    *mPointer2 = 20;
    mPointer2 = mPointer1;
    EXPECT_EQ(*mPointer2, 10);
    EXPECT_TRUE(mPointer1 == mPointer2);
}

TEST_F(MPointerTest, EqualityOperator) {
    const auto mPointer1 = MPointer<int>::New();
    auto mPointer2 = MPointer<int>::New();
    EXPECT_FALSE(mPointer1 == mPointer2);
    mPointer2 = mPointer1;
    EXPECT_TRUE(mPointer1 == mPointer2);
}