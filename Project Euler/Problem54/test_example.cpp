
#include <gtest/gtest.h>

// A simple function to test
int add(int a, int b) {
    return a + b;
}

// A basic Google Test case
TEST(AdditionTest, BasicAssertions) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(10, 20), 30);
    EXPECT_NE(add(1, 1), 3);
}