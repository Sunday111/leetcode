#include "001_two_sum.hpp"
#include "gtest/gtest.h"

TEST(s001_two_sum, test_1)
{
    Solution s{};

    std::vector input{2, 7, 11, 15};
    std::vector expected{0, 1};
    ASSERT_EQ(s.twoSum(input, 9), expected);
}

TEST(s001_two_sum, test_2)
{
    Solution s{};

    std::vector input{3, 2, 4};
    std::vector expected{1, 2};
    ASSERT_EQ(s.twoSum(input, 6), expected);
}

TEST(s001_two_sum, test_3)
{
    Solution s{};

    std::vector input{3, 3};
    std::vector expected{0, 1};
    ASSERT_EQ(s.twoSum(input, 6), expected);
}
