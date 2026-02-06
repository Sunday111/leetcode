#include "3634_minimum_removals_to_balance_array.hpp"
#include "gtest/gtest.h"

TEST(t3634_minimum_removals_to_balance_array, test_1)
{
    std::vector nums{2, 1, 5};
    u32 k = 2;
    u32 expected = 1;
    ASSERT_EQ(Solution{}.minRemoval(nums, k), expected);
}

TEST(t3634_minimum_removals_to_balance_array, test_2)
{
    std::vector nums{1, 6, 2, 9};
    u32 k = 3;
    u32 expected = 2;
    ASSERT_EQ(Solution{}.minRemoval(nums, k), expected);
}

TEST(t3634_minimum_removals_to_balance_array, test_3)
{
    std::vector nums{4, 6};
    u32 k = 2;
    u32 expected = 0;
    ASSERT_EQ(Solution{}.minRemoval(nums, k), expected);
}

TEST(t3634_minimum_removals_to_balance_array, test_4)
{
    std::vector nums{1, 34, 23};
    u32 k = 2;
    u32 expected = 1;
    ASSERT_EQ(Solution{}.minRemoval(nums, k), expected);
}
