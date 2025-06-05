#include "1260_shift_2d_grid.hpp"
#include "gtest/gtest.h"

TEST(t1260_shift_2d_grid, test_1)
{
    std::vector<std::vector<int>> grid{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    std::vector<std::vector<int>> expected{
        {9, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
    };
    auto actual = Solution{}.shiftGrid(grid, 1);
    ASSERT_EQ(expected, actual);
}
