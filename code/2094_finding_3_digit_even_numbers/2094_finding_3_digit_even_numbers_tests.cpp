#include "2094_finding_3_digit_even_numbers.hpp"
#include "gtest/gtest.h"

TEST(t2094_finding_3_digit_even_numbers, test_1)
{
    Solution s{};
    std::vector digits{1, 2, 3};
    std::vector<int> expected{132, 312};
    auto actual = s.findEvenNumbers(digits);
    ASSERT_EQ(expected, actual);
}

TEST(t2094_finding_3_digit_even_numbers, test_2)
{
    Solution s{};
    std::vector digits{2, 1, 3, 0};
    std::vector<int> expected{102, 120, 130, 132, 210, 230, 302, 310, 312, 320};
    auto actual = s.findEvenNumbers(digits);
    ASSERT_EQ(expected, actual);
}

TEST(t2094_finding_3_digit_even_numbers, test_3)
{
    Solution s{};
    std::vector digits{2, 2, 8, 8, 2};
    std::vector<int> expected{222, 228, 282, 288, 822, 828, 882};
    auto actual = s.findEvenNumbers(digits);
    ASSERT_EQ(expected, actual);
}

TEST(t2094_finding_3_digit_even_numbers, test_4)
{
    Solution s{};
    std::vector digits{3, 7, 5};
    std::vector<int> expected{};
    auto actual = s.findEvenNumbers(digits);
    ASSERT_EQ(expected, actual);
}
