#include "2359_find_closest_node_to_given_two_nodes.hpp"
#include "gtest/gtest.h"

TEST(t2359_find_closest_node_to_given_two_nodes, test_1)
{
    std::vector edges{4, 4, 8, -1, 9, 8, 4, 4, 1, 1};
    std::println("Graph:");
    for (size_t i = 0; i != edges.size(); ++i)
    {
        std::println("    {} -> {}", i, edges[i]);
    }
    ASSERT_EQ(Solution{}.closestMeetingNode(edges, 5, 6), 1);
}
