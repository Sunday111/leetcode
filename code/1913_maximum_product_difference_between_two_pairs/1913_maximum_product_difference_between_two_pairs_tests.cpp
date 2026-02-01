#include "1913_maximum_product_difference_between_two_pairs.hpp"
#include "gtest/gtest.h"

TEST(t1913_maximum_product_difference_between_two_pairs, test_1)
{
    std::vector nums{5, 6, 2, 7, 4};
    u32 expected = 34;
    u32 actual = Solution{}.maxProductDifference(nums);
    ASSERT_EQ(expected, actual);
}
