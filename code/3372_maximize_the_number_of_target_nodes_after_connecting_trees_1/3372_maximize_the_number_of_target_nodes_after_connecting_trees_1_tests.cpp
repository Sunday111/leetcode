#include "3372_maximize_the_number_of_target_nodes_after_connecting_trees_1.hpp"
#include "gtest/gtest.h"

TEST(t3372_maximize_the_number_of_target_nodes_after_connecting_trees_1, test_1)
{
    std::vector<std::vector<int>> edges1 = {
        {0, 1},
        {0, 2},
        {2, 3},
        {2, 4},
    };
    std::vector<std::vector<int>> edges2 = {
        {0, 1},
        {0, 2},
        {0, 3},
        {2, 7},
        {1, 4},
        {4, 5},
        {4, 6},
    };
    std::vector<int> expected{9, 7, 9, 8, 8};
    auto actual = Solution{}.maxTargetNodes(edges1, edges2, 2);
    ASSERT_EQ(expected, actual);
}
