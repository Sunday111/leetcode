#include "0885_spiral_matrix_3.hpp"
#include "gtest/gtest.h"

TEST(t0885_spiral_matrix_3, test_1)
{
    std::vector<std::vector<int>> expected{
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    };
    auto actual = Solution{}.spiralMatrixIII(1, 4, 0, 0);
    ASSERT_EQ(expected, actual);
}

TEST(t0885_spiral_matrix_3, test_2)
{
    std::vector<std::vector<int>> expected{
        {{1, 4}, {1, 5}, {2, 5}, {2, 4}, {2, 3}, {1, 3}, {0, 3}, {0, 4},
         {0, 5}, {3, 5}, {3, 4}, {3, 3}, {3, 2}, {2, 2}, {1, 2}, {0, 2},
         {4, 5}, {4, 4}, {4, 3}, {4, 2}, {4, 1}, {3, 1}, {2, 1}, {1, 1},
         {0, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    };
    auto actual = Solution{}.spiralMatrixIII(5, 6, 1, 4);
    ASSERT_EQ(expected, actual);
}
