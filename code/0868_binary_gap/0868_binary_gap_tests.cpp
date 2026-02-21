#include "0868_binary_gap.hpp"
#include "gtest/gtest.h"

TEST(t0868_binary_gap, test_1)
{
    ASSERT_EQ(Solution{}.binaryGap(22), 2);
    ASSERT_EQ(Solution{}.binaryGap(8), 0);
    ASSERT_EQ(Solution{}.binaryGap(5), 2);
}
