#include "0128_longest_consecutive_sequence.hpp"
#include "gtest/gtest.h"

TEST(t0128_longest_consecutive_sequence, test_1)
{
    std::vector nums{100, 4, 200, 1, 3, 2};
    ASSERT_EQ(Solution{}.longestConsecutive(nums), 4);
}

TEST(t0128_longest_consecutive_sequence, test_2)
{
    std::vector nums{0, -1};
    ASSERT_EQ(Solution{}.longestConsecutive(nums), 2);
}
