#include "0054_spiral_matrix.hpp"
#include "gtest/gtest.h"

TEST(t0054_spiral_matrix, test_1)
{
    const std::vector<std::vector<int>> matrix{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    const std::vector expected{1, 2, 3, 6, 9, 8, 7, 4, 5};
    const auto actual = Solution{}.spiralOrder(matrix);
    ASSERT_EQ(expected, actual);
}
