#include "0242_valid_anagram.hpp"
#include "gtest/gtest.h"

TEST(t0242_valid_anagram, test_1)
{
    Solution s{};
    ASSERT_EQ(s.isAnagram("anagram", "nagaram"), true);
}

TEST(t0242_valid_anagram, test_2)
{
    Solution s{};
    ASSERT_EQ(s.isAnagram("rat", "car"), false);
}
