#include <MPointerGC.h>
#include <gtest/gtest.h>
#include <MPointer.h>


class MPointerGCTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC::getInstance();
    }

    void TearDown() override {
        MPointerGC::getInstance()->stop();
    }
};


TEST_F(MPointerGCTest, GarbageCollectorStopsCorrectly) {
    {
        MPointer<int> myPtr = MPointer<int>::New();
        *myPtr = 20;

        MPointer<int> myPtr2 = MPointer<int>::New();
        myPtr2 = myPtr;

        EXPECT_EQ(*myPtr2, 20);
    }

    MPointerGC* gc = MPointerGC::getInstance();
    gc->stop();  // Try to stop the GC
    EXPECT_FALSE(gc->isRunning());  // Check if the GC is not running
}

TEST_F(MPointerGCTest, MultiplePointersAndGCBehavior) {
    MPointer<int> ptr1 = MPointer<int>::New();
    MPointer<int> ptr2 = MPointer<int>::New();
    MPointer<int> ptr3 = MPointer<int>::New();

    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;

    EXPECT_EQ(*ptr1, 1);
    EXPECT_EQ(*ptr2, 2);
    EXPECT_EQ(*ptr3, 3);

    ptr2 = ptr1;

    EXPECT_EQ(*ptr2, 1);
    EXPECT_EQ(*ptr1, 1);
}

TEST_F(MPointerGCTest, GarbageCollectorRunsAndCleansUp) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 50;

    {
        MPointer<int> ptr2 = MPointer<int>::New();
        *ptr2 = 100;

        EXPECT_EQ(*ptr2, 100);
    }

    // Wait for the GC to clean up
    std::this_thread::sleep_for(std::chrono::seconds(6));

    EXPECT_EQ(*ptr1, 50);
}

TEST_F(MPointerGCTest, PointerListSizeDecreases) {
    MPointerGC* gc = MPointerGC::getInstance();

    MPointer<int> myPtr = MPointer<int>::New();
    const size_t sizeBefore = gc->getMPointersCount();
    EXPECT_GT(sizeBefore, 0);

    {
        MPointer<int> myPtr2 = MPointer<int>::New();
        EXPECT_EQ(gc->getMPointersCount(), sizeBefore + 1);  // Size should have increased
    }

    // Wait for the GC to clean up
    std::this_thread::sleep_for(std::chrono::seconds(15));

    // Check if the size has decreased
    const size_t sizeAfter = gc->getMPointersCount();
    EXPECT_EQ(sizeAfter, sizeBefore);
}