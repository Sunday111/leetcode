#include "3818_minimum_prefix_removal_to_make_array_strictly_increasing.hpp"
#include "gtest/gtest.h"

TEST(t3818_minimum_prefix_removal_to_make_array_strictly_increasing, test_1)
{
    std::vector nums{1, -1, 2, 3, 3, 4, 5};
    ASSERT_EQ(Solution{}.minimumPrefixLength(nums), 4);
}

TEST(t3818_minimum_prefix_removal_to_make_array_strictly_increasing, test_2)
{
    std::vector nums{4, 3, -2, -5};
    ASSERT_EQ(Solution{}.minimumPrefixLength(nums), 3);
}

TEST(t3818_minimum_prefix_removal_to_make_array_strictly_increasing, test_3)
{
    std::vector nums{1, 2, 3, 4};
    ASSERT_EQ(Solution{}.minimumPrefixLength(nums), 0);
}
