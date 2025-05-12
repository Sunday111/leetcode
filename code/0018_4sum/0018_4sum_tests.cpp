#include "0018_4sum.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

TEST(t0018_4sum, test_1)
{
    Solution s{};
    std::vector nums{1, 0, -1, 0, -2, 2};
    constexpr int target = 0;
    std::vector<std::vector<int>> expected{
        {-2, -1, 1, 2},
        {-2, 0, 0, 2},
        {-1, 0, 0, 1}};

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_2)
{
    Solution s{};
    std::vector nums{1, 0, -1, 0, -2, 2};
    constexpr int target = 0;
    std::vector<std::vector<int>> expected{
        {-2, -1, 1, 2},
        {-2, 0, 0, 2},
        {-1, 0, 0, 1}};

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_3)
{
    Solution s{};
    std::vector nums{2, 2, 2, 2, 2};
    constexpr int target = 8;
    std::vector<std::vector<int>> expected{
        {2, 2, 2, 2},
    };

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_4)
{
    Solution s{};
    std::vector nums{0, 0, 0, 0};
    constexpr int target = 0;
    std::vector<std::vector<int>> expected{
        {0, 0, 0, 0},
    };

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_5)
{
    Solution s{};
    std::vector nums{-3, -1, 0, 2, 4, 5};
    constexpr int target = 0;
    std::vector<std::vector<int>> expected{
        {-3, -1, 0, 4},
    };

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_6)
{
    Solution s{};
    std::vector nums{1000000000, 1000000000, 1000000000, 1000000000};
    constexpr int target = 0;
    std::vector<std::vector<int>> expected{};

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0018_4sum, test_7)
{
    Solution s{};
    std::vector nums{0, 4, -5, 2, -2, 4, 2, -1, 4};
    constexpr int target = 12;
    std::vector<std::vector<int>> expected{
        {0, 4, 4, 4},
        {2, 2, 4, 4},
    };

    auto actual = s.fourSum(nums, target);
    ASSERT_EQ(sorted(expected), sorted(actual));
}
