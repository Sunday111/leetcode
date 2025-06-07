#include "3170_lexicographically_minimum_string_after_removing_stars.hpp"
#include "gtest/gtest.h"

TEST(t3170_lexicographically_minimum_string_after_removing_stars, test_1)
{
    EXPECT_EQ(Solution{}.clearStars("aaba*"), "aab");
    EXPECT_EQ(Solution{}.clearStars("abc"), "abc");
    EXPECT_EQ(Solution{}.clearStars("b*n"), "n");
    EXPECT_EQ(Solution{}.clearStars("aaba*"), "aab");
    EXPECT_EQ(Solution{}.clearStars("abc*de*fgh*"), "defgh");
    EXPECT_EQ(Solution{}.clearStars("a*b*c*d*"), "");
    EXPECT_EQ(Solution{}.clearStars("abcde*f*"), "cdef");
    EXPECT_EQ(Solution{}.clearStars("d*yed"), "yed");
}
