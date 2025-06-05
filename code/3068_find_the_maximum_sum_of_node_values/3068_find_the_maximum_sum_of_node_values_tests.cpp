#include "3068_find_the_maximum_sum_of_node_values.hpp"
#include "gtest/gtest.h"

TEST(t3068_find_the_maximum_sum_of_node_values, test_1)
{
    std::vector nums{67, 13, 79, 13, 75, 11, 0, 41, 94};
    std::vector<std::vector<int>> edges{
        {0, 1},
        {3, 7},
        {4, 7},
        {6, 5},
        {6, 0},
        {0, 2},
        {7, 2},
        {7, 8},
    };
    constexpr int k = 7;
    constexpr int64_t expected = 407;
    int64_t actual = Solution{}.maximumValueSum(nums, k, edges);
    ASSERT_EQ(actual, expected);
}
