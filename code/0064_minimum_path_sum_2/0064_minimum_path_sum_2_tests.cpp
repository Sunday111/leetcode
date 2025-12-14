#include "0064_minimum_path_sum_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t0064_minimum_path_sum_2, test_1)
{
    auto grid = parse2DArray("[[1,3,1],[1,5,1],[4,2,1]]");
    ASSERT_EQ(Solution{}.minPathSum(grid), 7);
}

TEST(t0064_minimum_path_sum_2, test_2)
{
    auto grid = parse2DArray(" [[1,2,3],[4,5,6]]");
    ASSERT_EQ(Solution{}.minPathSum(grid), 12);
}
