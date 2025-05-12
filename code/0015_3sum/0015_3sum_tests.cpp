#include "0015_3sum.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

TEST(t0015_3sum, test_1)
{
    std::vector input{-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> expected{
        {-1, -1, 2},
        {-1, 0, 1},
    };
    auto actual = Solution{}.threeSum(input);
    ASSERT_EQ(sorted(actual), sorted(expected));
}

TEST(t0015_3sum, test_2)
{
    std::vector input{0, 1, 1};
    std::vector<std::vector<int>> expected{};
    auto actual = Solution{}.threeSum(input);
    ASSERT_EQ(sorted(actual), sorted(expected));
}

TEST(t0015_3sum, test_3)
{
    std::vector input{0, 0, 0};
    std::vector<std::vector<int>> expected{
        {0, 0, 0},
    };
    auto actual = Solution{}.threeSum(input);
    ASSERT_EQ(sorted(actual), sorted(expected));
}
