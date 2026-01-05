#include "1975_maximum_matrix_sum.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t1975_maximum_matrix_sum, test_1)
{
    ASSERT_EQ(Solution{}.maxMatrixSum(parse2DArray("[[1,-1],[-1,1]]")), 4);
}

TEST(t1975_maximum_matrix_sum, test_2)
{
    ASSERT_EQ(
        Solution{}.maxMatrixSum(parse2DArray("[[1,2,3],[-1,-2,-3],[1,2,3]]")),
        16);
}

TEST(t1975_maximum_matrix_sum, test_3)
{
    ASSERT_EQ(
        Solution{}.maxMatrixSum(parse2DArray("[[2,9,3],[5,4,-4],[1,7,1]]")),
        34);
}

TEST(t1975_maximum_matrix_sum, test_4)
{
    ASSERT_EQ(
        Solution{}.maxMatrixSum(parse2DArray(
            "[[-10000,-10000,-10000],[-10000,-10000,-10000],[-10000,-10000,-"
            "10000]]")),
        70000);
}
