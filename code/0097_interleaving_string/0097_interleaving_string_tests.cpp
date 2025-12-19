#include "0097_interleaving_string.hpp"
#include "gtest/gtest.h"

// TEST(t0097_interleaving_string, test_1)
// {
//     ASSERT_EQ(Solution{}.isInterleave("aabcc", "dbbca", "aadbbcbcac"), true);
// }
// TEST(t0097_interleaving_string, test_2)
// {
//     ASSERT_EQ(Solution{}.isInterleave("aabcc", "dbbca", "aadbbbaccc"),
//     false);
// }
TEST(t0097_interleaving_string, test_3)
{
    ASSERT_EQ(Solution{}.isInterleave("ab", "bc", "babc"), true);
}
