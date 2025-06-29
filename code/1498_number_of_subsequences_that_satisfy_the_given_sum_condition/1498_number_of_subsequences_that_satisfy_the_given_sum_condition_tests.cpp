#include "1498_number_of_subsequences_that_satisfy_the_given_sum_condition.hpp"
#include "gtest/gtest.h"

TEST(t1498_number_of_subsequences_that_satisfy_the_given_sum_condition, test_1)
{
    std::vector nums{3, 5, 6, 7};
    ASSERT_EQ(Solution{}.numSubseq(nums, 9), 4);
}

TEST(t1498_number_of_subsequences_that_satisfy_the_given_sum_condition, test_2)
{
    std::vector nums{5, 2, 4, 1, 7, 6, 8};
    ASSERT_EQ(Solution{}.numSubseq(nums, 16), 127);
}

TEST(t1498_number_of_subsequences_that_satisfy_the_given_sum_condition, test_3)
{
    std::vector nums{28, 17, 24, 3,  3,  28, 14, 9,  10, 4,  30, 30, 28, 10,
                     20, 27, 19, 19, 12, 25, 23, 5,  19, 2,  15, 12, 1,  22,
                     12, 21, 19, 2,  15, 21, 8,  21, 15, 26, 8,  11, 5,  4,
                     11, 20, 16, 10, 16, 6,  21, 19, 12, 1,  26, 19};
    ASSERT_EQ(Solution{}.numSubseq(nums, 29), 885784560);
}
