#include "0059_spiral_matrix_2.hpp"
#include "gtest/gtest.h"

TEST(t0059_spiral_matrix_2, test_1)
{
    std::vector<std::vector<int>> expected{
        {1, 2, 3},
        {8, 9, 4},
        {7, 6, 5},
    };
    auto actual = Solution{}.generateMatrix(3);
    ASSERT_EQ(expected, actual);
}
