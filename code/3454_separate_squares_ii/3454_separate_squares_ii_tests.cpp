#include "3454_separate_squares_ii.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3454_separate_squares_ii, test_1)
{
    auto arr = parse2DArray("[[0,0,1],[2,2,1]]");
    ASSERT_EQ(Solution{}.separateSquares(arr), 1);
}

TEST(t3454_separate_squares_ii, test_2)
{
    auto arr = parse2DArray("[[0,0,2],[1,1,1]]");
    ASSERT_EQ(Solution{}.separateSquares(arr), 1);
}

TEST(t3454_separate_squares_ii, test_3)
{
    auto arr = parse2DArray("[[15,21,2],[19,21,3]]");
    ASSERT_EQ(Solution{}.separateSquares(arr), 22.3);
}
