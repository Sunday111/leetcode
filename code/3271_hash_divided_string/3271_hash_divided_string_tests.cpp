#include "3271_hash_divided_string.hpp"
#include "gtest/gtest.h"

TEST(t3271_hash_divided_string, test_1)
{
    std::string orig = "abcd";
    u8 k = 2;
    std::string_view expected = "bf";
    auto actual = Solution{}.stringHash(orig, k);
    ASSERT_EQ(expected, actual);
}

TEST(t3271_hash_divided_string, test_2)
{
    std::string orig = "mxz";
    u8 k = 3;
    std::string_view expected = "i";
    auto actual = Solution{}.stringHash(orig, k);
    ASSERT_EQ(expected, actual);
}

TEST(t3271_hash_divided_string, test_3)
{
    std::string orig = "hcr";
    u8 k = 3;
    std::string_view expected = "a";
    auto actual = Solution{}.stringHash(orig, k);
    ASSERT_EQ(expected, actual);
}
