#include "0693_binary_number_with_alternating_bits.hpp"
#include "gtest/gtest.h"

TEST(t0693_binary_number_with_alternating_bits, test_1)
{
    ASSERT_EQ(Solution{}.hasAlternatingBits(5), true);
    ASSERT_EQ(Solution{}.hasAlternatingBits(7), false);
    ASSERT_EQ(Solution{}.hasAlternatingBits(11), false);
}
