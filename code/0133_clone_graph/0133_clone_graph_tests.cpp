
#include "0133_clone_graph.hpp"
#include "gtest/gtest.h"
#include "leet_code_unidirected_graph.hpp"

using Graph = LeetCodeUnidirectedGraph<Node>;

TEST(t0133_clone_graph, test_graph)
{
    constexpr std::string_view input_al_str = "[[2,4],[1,3],[2,4],[1,3]]";

    {
        std::vector<std::vector<uint32_t>> expected{
            {2, 4},
            {1, 3},
            {2, 4},
            {1, 3}};
        auto actual = Graph::ParseAdjacencyList(input_al_str);
        ASSERT_EQ(expected, actual);
    }

    auto graph = Graph::FromAdjacencyListStr(input_al_str, 1);
    auto out_al_str = graph.MakeAdjacencyListStr();
    ASSERT_EQ(input_al_str, out_al_str);
}

TEST(t0133_clone_graph, test_1)
{
    constexpr std::string_view input_al_str = "[[2,4],[1,3],[2,4],[1,3]]";
    constexpr int default_value = 1;

    auto graph = Graph::FromAdjacencyListStr(input_al_str, default_value);

    Solution{}.cloneGraph(graph.GetRoot());
}
