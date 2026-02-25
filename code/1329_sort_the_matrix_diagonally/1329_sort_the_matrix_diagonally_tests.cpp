#include "1329_sort_the_matrix_diagonally.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t1329_sort_the_matrix_diagonally, test_1)
{
    auto orig = parse2DArray("[[3,3,1,1],[2,2,1,2],[1,1,1,2]]");
    auto expected = parse2DArray("[[1,1,1,1],[1,2,2,2],[1,2,3,3]]");
    auto actual = Solution::diagonalSort(orig);
    ASSERT_EQ(expected, actual);
}

TEST(t1329_sort_the_matrix_diagonally, test_2)
{
    auto orig = parse2DArray(
        "[[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,"
        "25,68,4],[84,28,14,11,5,50]]");
    auto expected = parse2DArray(
        "[[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,"
        "50,66],[84,28,75,33,55,68]]");
    auto actual = Solution::diagonalSort(orig);
    ASSERT_EQ(expected, actual);
}
