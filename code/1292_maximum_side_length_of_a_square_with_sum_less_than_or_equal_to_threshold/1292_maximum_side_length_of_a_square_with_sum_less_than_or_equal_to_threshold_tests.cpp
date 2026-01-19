#include "1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold, test_1)
{
    auto m = parse2DArray("[[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]]");
    unsigned threshold = 4;
    unsigned expected = 2;
    ASSERT_EQ(Solution{}.maxSideLength(m, threshold), expected);
}
