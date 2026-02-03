#include "3640_trionic_array_ii.hpp"
#include "gtest/gtest.h"

TEST(t3640_trionic_array_ii, test_1)
{
    std::vector nums{0, -2, -1, -3, 0, 2, -1};
    ASSERT_EQ(Solution{}.maxSumTrionic(nums), -4);
}

TEST(t3640_trionic_array_ii, test_2)
{
    std::vector nums{1, 4, 2, 7};
    ASSERT_EQ(Solution{}.maxSumTrionic(nums), 14);
}
