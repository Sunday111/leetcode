#include "3202_find_the_maximum_length_of_valid_subsequence_2.hpp"
#include "gtest/gtest.h"

TEST(t3202_find_the_maximum_length_of_valid_subsequence_2, test_1)
{
    ASSERT_EQ(Solution{}.maximumLength({1, 2, 3, 4, 5}, 2), 5);
}
TEST(t3202_find_the_maximum_length_of_valid_subsequence_2, test_2)
{
    ASSERT_EQ(Solution{}.maximumLength({1, 9, 3, 10, 10}, 4), 2);
}
