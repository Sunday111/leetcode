#include "1461_check_if_a_string_contains_all_binary_codes_of_size_k.hpp"
#include "gtest/gtest.h"

TEST(t1461_check_if_a_string_contains_all_binary_codes_of_size_k, test_1)
{
    ASSERT_EQ(Solution{}.hasAllCodes("00110110", 2), true);
}

TEST(t1461_check_if_a_string_contains_all_binary_codes_of_size_k, test_2)
{
    ASSERT_EQ(Solution{}.hasAllCodes("0110", 1), true);
}

TEST(t1461_check_if_a_string_contains_all_binary_codes_of_size_k, test_3)
{
    ASSERT_EQ(Solution{}.hasAllCodes("0110", 2), false);
}

TEST(t1461_check_if_a_string_contains_all_binary_codes_of_size_k, test_4)
{
    ASSERT_EQ(Solution{}.hasAllCodes("00110", 2), true);
}
