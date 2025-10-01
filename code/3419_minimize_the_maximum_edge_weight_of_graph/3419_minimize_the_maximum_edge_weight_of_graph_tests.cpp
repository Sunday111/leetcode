#include "3419_minimize_the_maximum_edge_weight_of_graph.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3419_minimize_the_maximum_edge_weight_of_graph, test_1)
{
    auto edges = parse2DArray("[[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]]");
    ASSERT_EQ(Solution{}.minMaxWeight(5, edges, 2), 1);
}
