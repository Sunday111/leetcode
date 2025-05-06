#include <algorithm>

#include "0282_expression_add_operators.hpp"
#include "gtest/gtest.h"

TEST(t0282_expression_add_operators, test_1)
{
    std::string_view string = "123";
    int32_t target = 6;
    std::vector<std::string> expected = {"1*2*3", "1+2+3"};
    std::vector<std::string> actual = Solution{}.addOperators(string, target);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

TEST(t0282_expression_add_operators, test_2)
{
    std::string_view string = "232";
    int32_t target = 8;
    std::vector<std::string> expected = {"2*3+2", "2+3*2"};
    std::vector<std::string> actual = Solution{}.addOperators(string, target);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

TEST(t0282_expression_add_operators, test_3)
{
    std::string_view string = "3456237490";
    int32_t target = 9191;
    std::vector<std::string> expected = {};
    std::vector<std::string> actual = Solution{}.addOperators(string, target);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

TEST(t0282_expression_add_operators, test_4)
{
    std::string_view string = "105";
    int32_t target = 5;
    std::vector<std::string> expected = {"1*0+5", "10-5"};
    std::vector<std::string> actual = Solution{}.addOperators(string, target);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}
