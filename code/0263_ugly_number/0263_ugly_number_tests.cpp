#include "0263_ugly_number.hpp"
#include "gtest/gtest.h"

TEST(t0263_ugly_number, test_1)
{
    EXPECT_EQ(Solution{}.isUgly(0), false);
    EXPECT_EQ(Solution{}.isUgly(1), true);
    EXPECT_EQ(Solution{}.isUgly(6), true);
    EXPECT_EQ(Solution{}.isUgly(14), false);
}
