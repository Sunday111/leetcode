#include "3650_minimum_cost_path_with_edge_reversals.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3650_minimum_cost_path_with_edge_reversals, test_1)
{
    auto edges = parse2DArray("[[0,1,3],[3,1,1],[2,3,4],[0,2,2]]");
    constexpr u32 n = 4;
    constexpr int expected = 5;
    ASSERT_EQ(Solution {}.minCost(n, edges), expected);
}

TEST(t3650_minimum_cost_path_with_edge_reversals, test_2)
{
    auto edges = parse2DArray("[[0,2,1],[2,1,1],[1,3,1],[2,3,3]]");
    constexpr u32 n = 4;
    constexpr int expected = 3;
    ASSERT_EQ(Solution {}.minCost(n, edges), expected);
}

TEST(t3650_minimum_cost_path_with_edge_reversals, test_3)
{
    auto edges = parse2DArray("[[2,3,25],[2,1,18],[3,1,2]]");
    constexpr u32 n = 4;
    constexpr int expected = -1;
    ASSERT_EQ(Solution {}.minCost(n, edges), expected);
}
