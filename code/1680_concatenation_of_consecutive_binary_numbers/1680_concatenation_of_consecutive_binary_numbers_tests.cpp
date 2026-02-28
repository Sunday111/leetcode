#include "1680_concatenation_of_consecutive_binary_numbers.hpp"
#include "gtest/gtest.h"

TEST(t1680_concatenation_of_consecutive_binary_numbers, test_1)
{
    ASSERT_EQ(Solution{}.concatenatedBinary(1), 1);
}

TEST(t1680_concatenation_of_consecutive_binary_numbers, test_2)
{
    ASSERT_EQ(Solution{}.concatenatedBinary(3), 27);
}

TEST(t1680_concatenation_of_consecutive_binary_numbers, test_3)
{
    ASSERT_EQ(Solution{}.concatenatedBinary(12), 505379714);
}

TEST(t1680_concatenation_of_consecutive_binary_numbers, test_4)
{
    ASSERT_EQ(Solution{}.concatenatedBinary(90999), 459883164);
}

TEST(t1680_concatenation_of_consecutive_binary_numbers, test_5)
{
    ASSERT_EQ(Solution{}.concatenatedBinary(100000), 757631812);
}
