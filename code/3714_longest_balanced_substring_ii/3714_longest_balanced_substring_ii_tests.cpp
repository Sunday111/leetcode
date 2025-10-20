#include <fstream>

#include "3714_longest_balanced_substring_ii.hpp"
#include "gtest/gtest.h"

TEST(t3714_longest_balanced_substring_ii, test_1)
{
    ASSERT_EQ(Solution{}.longestBalanced("abbac"), 4);
}

TEST(t3714_longest_balanced_substring_ii, test_2)
{
    ASSERT_EQ(Solution{}.longestBalanced("aabcc"), 3);
}

TEST(t3714_longest_balanced_substring_ii, test_3)
{
    ASSERT_EQ(Solution{}.longestBalanced("aba"), 2);
}

TEST(t3714_longest_balanced_substring_ii, test_4)
{
    std::string path = LC_TARGET_SRC_PATH;
    path += "/big_test_case.txt";
    ASSERT_EQ(Solution{}.longestBalanced("aba"), 2);
    std::ifstream file(path);
    ASSERT_TRUE(file.is_open());
    std::string content;
    ASSERT_TRUE(std::getline(file, content));

    ASSERT_EQ(Solution{}.longestBalanced(content), 14355);
}

TEST(t3714_longest_balanced_substring_ii, test_5)
{
    ASSERT_EQ(Solution{}.longestBalanced("bacbbc"), 4);
}
