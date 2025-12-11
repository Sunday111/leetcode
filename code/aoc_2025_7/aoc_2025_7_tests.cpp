#include "aoc_2025_7.hpp"
#include "gtest/gtest.h"

TEST(taoc_2025_7, DISABLED_test_sample_1)
{
    ASSERT_EQ(Solution1{}.solve(kSampleInput), 21);
}

TEST(taoc_2025_7, DISABLED_test_input_1)
{
    ASSERT_EQ(Solution1{}.solve(kMyInput), 1562);
}

TEST(taoc_2025_7, DISABLED_test_sample_2)
{
    ASSERT_EQ(Solution2{}.solve(kSampleInput), 40);
}

TEST(taoc_2025_7, DISABLED_test_input_2)
{
    ASSERT_EQ(Solution2{}.solve(kMyInput), 24292631346665);
}
