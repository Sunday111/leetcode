#include "2246_longest_path_with_different_adjacent_characters.hpp"
#include "gtest/gtest.h"

TEST(t2246_longest_path_with_different_adjacent_characters, test_1)
{
    Solution s{};
    std::vector parent{-1, 0, 0, 1, 1, 2};
    std::string_view chars = "abacbe";
    ASSERT_EQ(s.longestPath(parent, chars), 3);
}

TEST(t2246_longest_path_with_different_adjacent_characters, test_2)
{
    Solution s{};
    std::vector parent{-1, 0, 0, 0};
    std::string_view chars = "aabc";
    ASSERT_EQ(s.longestPath(parent, chars), 3);
}
