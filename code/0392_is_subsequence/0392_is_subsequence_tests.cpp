#include "0392_is_subsequence.hpp"
#include "gtest/gtest.h"

TEST(t0392_is_subsequence, test_1)
{
    ASSERT_EQ(Solution{}.isSubsequence("aaaaaa", "bbaaaa"), false);
    ASSERT_EQ(Solution{}.isSubsequence("abc", "ahbgdc"), true);
    ASSERT_EQ(Solution{}.isSubsequence("axc", "ahbgdc"), false);
}
