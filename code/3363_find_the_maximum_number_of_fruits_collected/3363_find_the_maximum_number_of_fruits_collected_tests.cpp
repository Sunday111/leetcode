#include "3363_find_the_maximum_number_of_fruits_collected.hpp"
#include "gtest/gtest.h"

TEST(t3363_find_the_maximum_number_of_fruits_collected, test_1)
{
    std::vector<std::vector<int>> fruits{
        {{1, 2, 3, 4}, {5, 6, 8, 7}, {9, 10, 11, 12}, {13, 14, 15, 16}}

    };

    ASSERT_EQ(Solution{}.maxCollectedFruits(fruits), 100);
}
