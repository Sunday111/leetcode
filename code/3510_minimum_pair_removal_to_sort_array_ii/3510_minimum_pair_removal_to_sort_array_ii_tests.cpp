#include "3510_minimum_pair_removal_to_sort_array_ii.hpp"
#include "gtest/gtest.h"

TEST(t3510_minimum_pair_removal_to_sort_array_ii, test_1)
{
    std::vector nums{5, 2, 3, 1};
    int expected = 2;
    ASSERT_EQ(Solution{}.minimumPairRemoval(nums), expected);
}

TEST(t3510_minimum_pair_removal_to_sort_array_ii, test_2)
{
    std::vector nums{1, 2, 2};
    int expected = 0;
    ASSERT_EQ(Solution{}.minimumPairRemoval(nums), expected);
}

TEST(t3510_minimum_pair_removal_to_sort_array_ii, test_3)
{
    std::vector nums{1, 1, 4, 1};
    int expected = 2;
    ASSERT_EQ(Solution{}.minimumPairRemoval(nums), expected);
}

TEST(t3510_minimum_pair_removal_to_sort_array_ii, test_4)
{
    std::vector nums{1, 1, 4, 4, 2, -4, -1};
    int expected = 5;
    ASSERT_EQ(Solution{}.minimumPairRemoval(nums), expected);
}

TEST(t3510_minimum_pair_removal_to_sort_array_ii, test_5)
{
    std::vector nums{3, 6, -9, 6, 3, -4};
    int expected = 4;
    ASSERT_EQ(Solution{}.minimumPairRemoval(nums), expected);
}
