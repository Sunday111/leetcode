#include "0438_find_all_anagrams_in_a_string.hpp"
#include "gtest/gtest.h"

TEST(t0438_find_all_anagrams_in_a_string, test_1)
{
    Solution sol{};
    constexpr std::string_view s = "cbaebabacd";
    constexpr std::string_view p = "abc";
    std::vector expected{0, 6};
    ASSERT_EQ(sol.findAnagrams(s, p), expected);
}

TEST(t0438_find_all_anagrams_in_a_string, test_2)
{
    Solution sol{};
    constexpr std::string_view s = "abab";
    constexpr std::string_view p = "ab";
    std::vector expected{0, 1, 2};
    ASSERT_EQ(sol.findAnagrams(s, p), expected);
}
