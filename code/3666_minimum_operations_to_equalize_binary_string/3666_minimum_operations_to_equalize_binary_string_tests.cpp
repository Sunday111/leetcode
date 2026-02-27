#include "3666_minimum_operations_to_equalize_binary_string.hpp"
#include "gtest/gtest.h"

TEST(t3666_minimum_operations_to_equalize_binary_string, test_1)
{
    std::string s = "110";
    constexpr int k = 1;
    int expected = 1;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_2)
{
    std::string s = "0101";
    constexpr int k = 3;
    int expected = 2;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_3)
{
    std::string s = "101";
    constexpr int k = 2;
    int expected = -1;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_4)
{
    std::string s = "10000000000000000000000000";
    constexpr int k = 2;
    int expected = -1;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_5)
{
    std::string s = "1100";
    constexpr int k = 3;
    int expected = 2;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_6)
{
    std::string s = "001";
    constexpr int k = 3;
    int expected = -1;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_7)
{
    std::string s = "0000";
    constexpr int k = 3;
    int expected = 4;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}

TEST(t3666_minimum_operations_to_equalize_binary_string, test_8)
{
    // 01000 4
    // 10100 3
    // 11111 0
    std::string s = "01000";
    constexpr int k = 3;
    int expected = 2;
    ASSERT_EQ(Solution{}.minOperations(s, k), expected);
}
