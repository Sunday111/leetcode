#include "2943_maximize_area_of_square_hole_in_grid.hpp"
#include "gtest/gtest.h"

TEST(t2943_maximize_area_of_square_hole_in_grid, test_1)
{
    int n = 2, m = 1;
    std::vector hBars{2, 3}, vBars{2};
    int expected = 4;
    ASSERT_EQ(Solution{}.maximizeSquareHoleArea(n, m, hBars, vBars), expected);
}

TEST(t2943_maximize_area_of_square_hole_in_grid, test_2)
{
    int n = 1, m = 1;
    std::vector hBars{2}, vBars{2};
    int expected = 4;
    ASSERT_EQ(Solution{}.maximizeSquareHoleArea(n, m, hBars, vBars), expected);
}

TEST(t2943_maximize_area_of_square_hole_in_grid, test_3)
{
    int n = 3, m = 2;
    std::vector hBars{3, 2, 4}, vBars{3, 2};
    int expected = 9;
    ASSERT_EQ(Solution{}.maximizeSquareHoleArea(n, m, hBars, vBars), expected);
}

TEST(t2943_maximize_area_of_square_hole_in_grid, test_4)
{
    int n = 4, m = 40;
    std::vector hBars{5, 3, 2, 4}, vBars{36, 41, 6, 34, 33};
    int expected = 9;
    ASSERT_EQ(Solution{}.maximizeSquareHoleArea(n, m, hBars, vBars), expected);
}
