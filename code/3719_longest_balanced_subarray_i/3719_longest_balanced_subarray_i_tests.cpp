#include "3719_longest_balanced_subarray_i.hpp"
#include "gtest/gtest.h"

TEST(t3719_longest_balanced_subarray_i, test_1)
{
    std::vector nums{2, 5, 4, 3};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 4);
}

TEST(t3719_longest_balanced_subarray_i, test_2)
{
    std::vector nums{3, 2, 2, 5, 4};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 5);
}

TEST(t3719_longest_balanced_subarray_i, test_3)
{
    std::vector nums{1, 2, 3, 2};
    ASSERT_EQ(Solution{}.longestBalanced(nums), 3);
}
