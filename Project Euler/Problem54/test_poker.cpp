
#include <gtest/gtest.h>

#include "poker.hpp"

// A basic Google Test case
TEST(hand_recognition, isStraightFlush) {
    
    std::vector<card> hand = {
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 6}
    };

    EXPECT_EQ(isStraightFlush(hand), 6);

}