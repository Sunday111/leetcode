#include "0415_add_strings.hpp"
#include "gtest/gtest.h"

TEST(t0415_add_strings, test_1)
{
    Solution s{};
    ASSERT_EQ(s.addStrings("11", "123"), "134");
}

TEST(t0415_add_strings, test_2)
{
    Solution s{};
    ASSERT_EQ(s.addStrings("1", "9"), "10");
}
