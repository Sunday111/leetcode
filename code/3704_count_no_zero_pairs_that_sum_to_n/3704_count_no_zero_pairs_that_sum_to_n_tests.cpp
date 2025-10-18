#include "3704_count_no_zero_pairs_that_sum_to_n.hpp"
#include "gtest/gtest.h"

TEST(t3704_count_no_zero_pairs_that_sum_to_n, test_1)
{
    ASSERT_EQ(
        Solution{}.countNoZeroPairs(1'000'000'000'000'000),
        50891681057058);
}
