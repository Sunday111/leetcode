#include "0827_Making_A_Large_Island.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t0827_Making_A_Large_Island, test_1)
{
    auto grid = parse2DArray("[[1,0],[0,1]]");
    u32 expected = 3;
    ASSERT_EQ(Solution{}.largestIsland(grid), expected);
}

TEST(t0827_Making_A_Large_Island, test_2)
{
    auto grid = parse2DArray("[[1,1],[1,1]]");
    u32 expected = 4;
    ASSERT_EQ(Solution{}.largestIsland(grid), expected);
}
