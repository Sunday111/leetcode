#include "0712_minimum_ascii_delete_sum_for_two_strings.hpp"
#include "gtest/gtest.h"

TEST(t0712_minimum_ascii_delete_sum_for_two_strings, test_1)
{
    ASSERT_EQ(Solution{}.minimumDeleteSum("sea", "eat"), 231);
}
