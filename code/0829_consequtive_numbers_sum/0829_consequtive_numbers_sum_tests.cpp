#include "0829_consequtive_numbers_sum.hpp"
#include "gtest/gtest.h"

TEST(t0829_consequtive_numbers_sum, test_1)
{
    ASSERT_EQ(Solution{}.consecutiveNumbersSum(5), 2);
}

TEST(t0829_consequtive_numbers_sum, test_2)
{
    ASSERT_EQ(Solution{}.consecutiveNumbersSum(9), 3);
}

TEST(t0829_consequtive_numbers_sum, test_3)
{
    ASSERT_EQ(Solution{}.consecutiveNumbersSum(15), 4);
}

TEST(t0829_consequtive_numbers_sum, test_4)
{
    ASSERT_EQ(Solution{}.consecutiveNumbersSum(999999), 64);
}

TEST(t0829_consequtive_numbers_sum, test_5)
{
    ASSERT_EQ(Solution{}.consecutiveNumbersSum(99999999), 48);
}
