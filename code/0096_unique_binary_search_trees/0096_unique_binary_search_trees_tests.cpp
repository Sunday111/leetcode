#include "0096_unique_binary_search_trees.hpp"
#include "gtest/gtest.h"

TEST(t0096_unique_binary_search_trees, test_1)
{
    ASSERT_EQ(Solution{}.numTrees(1), 1);
    ASSERT_EQ(Solution{}.numTrees(2), 2);
    ASSERT_EQ(Solution{}.numTrees(3), 5);
    ASSERT_EQ(Solution{}.numTrees(4), 14);
    ASSERT_EQ(Solution{}.numTrees(5), 42);
    ASSERT_EQ(Solution{}.numTrees(6), 132);
    ASSERT_EQ(Solution{}.numTrees(7), 429);
    ASSERT_EQ(Solution{}.numTrees(8), 1430);
    ASSERT_EQ(Solution{}.numTrees(19), 1767263190);
}
