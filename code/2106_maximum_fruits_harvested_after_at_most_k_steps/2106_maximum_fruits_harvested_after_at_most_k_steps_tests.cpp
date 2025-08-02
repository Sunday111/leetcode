#include "2106_maximum_fruits_harvested_after_at_most_k_steps.hpp"
#include "gtest/gtest.h"

TEST(t2106_maximum_fruits_harvested_after_at_most_k_steps, test_1)
{
    std::vector<std::vector<int>> fruits{
        {2, 8},
        {6, 3},
        {8, 6},
    };
    ASSERT_EQ(Solution{}.maxTotalFruits(fruits, 5, 4), 9);
}

TEST(t2106_maximum_fruits_harvested_after_at_most_k_steps, test_2)
{
    std::vector<std::vector<int>> fruits{
        {0, 9},
        {4, 1},
        {5, 7},
        {6, 2},
        {7, 4},
        {10, 9},
    };
    ASSERT_EQ(Solution{}.maxTotalFruits(fruits, 5, 4), 14);
}

TEST(t2106_maximum_fruits_harvested_after_at_most_k_steps, test_3)
{
    std::vector<std::vector<int>> fruits{
        {0, 3},
        {6, 4},
        {8, 5},
    };
    ASSERT_EQ(Solution{}.maxTotalFruits(fruits, 3, 2), 0);
}

TEST(t2106_maximum_fruits_harvested_after_at_most_k_steps, test_4)
{
    std::vector<std::vector<int>> fruits{
        {1, 9},
        {2, 10},
        {3, 1},
        {5, 6},
        {6, 3},
        {8, 2},
        {9, 2},
        {11, 4},
        {18, 10},
        {22, 8},
        {25, 2},
        {26, 2},
        {30, 4},
        {31, 5},
        {33, 9},
        {34, 1},
        {39, 10},
    };
    ASSERT_EQ(Solution{}.maxTotalFruits(fruits, 19, 9), 22);
}

TEST(t2106_maximum_fruits_harvested_after_at_most_k_steps, test_5)
{
    std::vector<std::vector<int>> fruits{
        {0, 10000},
    };
    ASSERT_EQ(Solution{}.maxTotalFruits(fruits, 200000, 200000), 10000);
}
