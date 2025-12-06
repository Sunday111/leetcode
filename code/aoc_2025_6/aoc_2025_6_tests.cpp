#include "aoc_2025_6.hpp"
#include "gtest/gtest.h"

TEST(taoc_2025_6, test_sample_1)
{
    ASSERT_EQ(Solution1{}.solve(kSampleInput), 4277556);
}

TEST(taoc_2025_6, test_input_1)
{
    ASSERT_EQ(Solution1{}.solve(kMyInput), 4387670995909);
}

TEST(taoc_2025_6, test_sample_2)
{
    ASSERT_EQ(Solution2{}.solve(kSampleInput), 3263827);
}

TEST(taoc_2025_6, test_input_2)
{
    ASSERT_EQ(Solution2{}.solve(kMyInput), 9625320374409);
}
