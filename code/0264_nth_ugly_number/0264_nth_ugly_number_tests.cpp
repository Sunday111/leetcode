#include "0264_nth_ugly_number.hpp"
#include "gtest/gtest.h"

TEST(t0264_nth_ugly_number, test_1)
{
    EXPECT_EQ(Solution{}.nthUglyNumber(10), 12);
    EXPECT_EQ(Solution{}.nthUglyNumber(1690), 2123366400);
}
