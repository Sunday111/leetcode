#include "3362_zero_array_transformation_3.hpp"
#include "gtest/gtest.h"

TEST(t3362_zero_array_transformation_3, test_1)
{
    std::vector<int> nums{2, 0, 2};
    std::vector<std::vector<int>> queries{
        {0, 2},
        {0, 2},
        {1, 1},
    };
    constexpr int expected = 1;
    ASSERT_EQ(Solution{}.maxRemoval(nums, queries), expected);
}

TEST(t3362_zero_array_transformation_3, test_2)
{
    std::vector<int> nums{1, 2, 3, 4};
    std::vector<std::vector<int>> queries{
        {0, 3},
    };
    constexpr int expected = -1;
    ASSERT_EQ(Solution{}.maxRemoval(nums, queries), expected);
}

TEST(t3362_zero_array_transformation_3, test_3)
{
    std::vector<int> nums{0, 3};
    std::vector<std::vector<int>> queries{
        {0, 0},
        {0, 0},
        {0, 1},
        {0, 1},
        {0, 1},
    };
    constexpr int expected = 2;
    ASSERT_EQ(Solution{}.maxRemoval(nums, queries), expected);
}
