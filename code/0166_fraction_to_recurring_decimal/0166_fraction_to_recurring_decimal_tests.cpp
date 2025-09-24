#include "0166_fraction_to_recurring_decimal.hpp"
#include "gtest/gtest.h"

TEST(t0166_fraction_to_recurring_decimal, test_1)
{
    int a = 4;
    int b = 333;
    std::println("{}/{} = {}", a, b, Solution::fractionToDecimal(a, b));
}

TEST(t0166_fraction_to_recurring_decimal, test_2)
{
    int a = 1;
    int b = 2;
    std::println("{}/{} = {}", a, b, Solution::fractionToDecimal(a, b));
}
