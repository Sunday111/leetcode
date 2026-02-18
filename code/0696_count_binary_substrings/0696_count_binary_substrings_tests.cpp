#include "0696_count_binary_substrings.hpp"
#include "gtest/gtest.h"

TEST(t0696_count_binary_substrings, test_1)
{
    ASSERT_EQ(Solution{}.countBinarySubstrings("00110011"), 6);
}
