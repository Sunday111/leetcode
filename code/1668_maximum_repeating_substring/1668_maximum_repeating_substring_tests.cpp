#include "1668_maximum_repeating_substring.hpp"
#include "gtest/gtest.h"

TEST(t1668_maximum_repeating_substring, test_1)
{
    ASSERT_EQ(Solution{}.maxRepeating("ababc", "ab"), 2);
    ASSERT_EQ(Solution{}.maxRepeating("ababc", "ba"), 1);
    ASSERT_EQ(Solution{}.maxRepeating("ababc", "ac"), 0);
    ASSERT_EQ(
        Solution{}.maxRepeating("aaabaaaabaaabaaaabaaaabaaaabaaaaba", "aaaba"),
        5);
}
