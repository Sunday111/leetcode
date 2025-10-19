#include "3713_longest_balanced_substring_i.hpp"
#include "gtest/gtest.h"

TEST(t3713_longest_balanced_substring_i, test_1)
{
    std::string s = "abbac";
    ASSERT_EQ(Solution{}.longestBalanced(s), 4);
}

TEST(t3713_longest_balanced_substring_i, test_2)
{
    std::string s = "nlllk";
    ASSERT_EQ(Solution{}.longestBalanced(s), 3);
}
