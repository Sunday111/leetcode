#include "1061_lexicographically_smallest_equivalent_string.hpp"
#include "gtest/gtest.h"

TEST(t1061_lexicographically_smallest_equivalent_string, test_1)
{
    ASSERT_EQ(
        Solution::smallestEquivalentString("parker", "morris", "parser"),
        "makkek");
}
