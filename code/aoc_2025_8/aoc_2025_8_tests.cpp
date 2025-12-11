#include "aoc_2025_8.hpp"
#include "gtest/gtest.h"

TEST(taoc_2025_8, DISABLED_test_sample_1)
{
    ASSERT_EQ(Solution1{}.solve(kSampleInput, 10), 40);
}

TEST(taoc_2025_8, DISABLED_test_input_1)
{
    ASSERT_EQ(Solution1{}.solve(kMyInput, 1000), 123420);
}

TEST(taoc_2025_8, DISABLED_test_sample_2)
{
    ASSERT_EQ(Solution2{}.solve(kSampleInput), 25272);
}

TEST(taoc_2025_8, DISABLED_test_input_2)
{
    ASSERT_EQ(Solution2{}.solve(kMyInput), 673096646);
}
