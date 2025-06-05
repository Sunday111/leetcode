#include "3373_maximize_the_number_of_target_nodes_after_connecting_trees_2.hpp"
#include "gtest/gtest.h"

TEST(t3373_maximize_the_number_of_target_nodes_after_connecting_trees_2, test_1)
{
    Solution s{};
    std::vector<std::vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    std::vector<std::vector<int>> edges2 =
        {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}};
    std::vector expected{8, 7, 7, 8, 8};
    auto actual = Solution{}.maxTargetNodes(edges1, edges2);
    ASSERT_EQ(expected, actual);
}

TEST(t3373_maximize_the_number_of_target_nodes_after_connecting_trees_2, test_2)
{
    Solution s{};
    std::vector<std::vector<int>> edges1 = {{2, 0}, {4, 1}, {2, 3}, {2, 4}};
    std::vector<std::vector<int>> edges2 = {{0, 1}, {0, 2}, {0, 3}};
    std::vector expected{6, 5, 5, 6, 6};
    auto actual = Solution{}.maxTargetNodes(edges1, edges2);
    ASSERT_EQ(expected, actual);
}
