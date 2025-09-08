#include "1317_convert_integer_to_the_sum_of_two_no_zero_integers.hpp"
#include "gtest/gtest.h"

TEST(t1317_convert_integer_to_the_sum_of_two_no_zero_integers, test_1)
{
    for (int sum = 2; sum != 10001; ++sum)
    {
        auto result = Solution{}.getNoZeroIntegers(sum);
        ASSERT_EQ(result[0] + result[1], sum);
        ASSERT_TRUE(Solution{}.no_zero_digits(result[0] & 0xFFFF));
        ASSERT_TRUE(Solution{}.no_zero_digits(result[1] & 0xFFFF));
    }
}
