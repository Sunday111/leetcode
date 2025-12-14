#include "0063_unique_paths_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t0063_unique_paths_2, test_1)
{
    auto grid = parse2DArray("[[0,0,0],[0,1,0],[0,0,0]]");
    ASSERT_EQ(Solution{}.uniquePathsWithObstacles(grid), 2);
}

TEST(t0063_unique_paths_2, test_2)
{
    auto grid = parse2DArray("[[0,1],[0,0]]");
    ASSERT_EQ(Solution{}.uniquePathsWithObstacles(grid), 1);
}

TEST(t0063_unique_paths_2, test_3)
{
    auto grid = parse2DArray("[[1,0]]");
    ASSERT_EQ(Solution{}.uniquePathsWithObstacles(grid), 0);
}
