#include "0953_verifying_an_alien_dictionary.hpp"
#include "gtest/gtest.h"

TEST(t0953_verifying_an_alien_dictionary, test_1)
{
    Solution s{};
    ASSERT_TRUE(
        s.isAlienSorted({"hello", "leetcode"}, "hlabcdefgijkmnopqrstuvwxyz"));
}
