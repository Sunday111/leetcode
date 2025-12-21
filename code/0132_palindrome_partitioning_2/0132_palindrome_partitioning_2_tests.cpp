#include "0132_palindrome_partitioning_2.hpp"
#include "gtest/gtest.h"

// TEST(t0132_palindrome_partitioning_2, test_1)
// {
//     ASSERT_EQ(Solution{}.minCut("ab"), 1);
// }
//
// TEST(t0132_palindrome_partitioning_2, test_2)
// {
//     ASSERT_EQ(Solution{}.minCut("cdd"), 1);
// }

TEST(t0132_palindrome_partitioning_2, test_3)
{
    ASSERT_EQ(Solution{}.minCut("abbab"), 1);
}
