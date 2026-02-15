#include "0067_add_binary.hpp"
#include "gtest/gtest.h"

TEST(t0067_add_binary, test_1)
{
    std::string a = "11", b = "1";
    std::string expected = "100";
    ASSERT_EQ(Solution{}.addBinary(a, b), expected);
}

TEST(t0067_add_binary, test_2)
{
    std::string a = "1010", b = "1011";
    std::string expected = "10101";
    ASSERT_EQ(Solution{}.addBinary(a, b), expected);
}
