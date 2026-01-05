#include "3798_largest_even_number.hpp"
#include "gtest/gtest.h"

TEST(t3798_largest_even_number, test_1)
{
    std::string s = "1112";
    ASSERT_EQ(Solution{}.largestEven(s), "1112");
}

TEST(t3798_largest_even_number, test_2)
{
    std::string s = "111";
    ASSERT_EQ(Solution{}.largestEven(s), "");
}
