#include "3794_reverse_string_prefix.hpp"
#include "gtest/gtest.h"

TEST(t3794_reverse_string_prefix, test_1)
{
    std::string s = "abcd";
    ASSERT_EQ(Solution{}.reversePrefix(s, 2), "bacd");
}
