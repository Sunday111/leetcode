#include <memory>
#include <unordered_set>

#include "0133_clone_graph.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "leet_code_unidirected_graph.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<u32>>>,
    std::vector<std::vector<u32>>>(R"cases(
[[2,4],[1,3],[2,4],[1,3]] [[2,4],[1,3],[2,4],[1,3]]
[[]] [[]]
[] []
)cases");

class t0133_clone_graph : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0133_clone_graph, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto graph = LeetCodeUnidirectedGraph<Node>::FromAdjacencyList(
        std::get<0>(inputs),
        1);
    for (u32 i = 0; i < graph.nodes.size(); ++i)
        graph.nodes[i].val = cast<int>(i + 1);
    auto* clone = Solution{}.cloneGraph(graph.GetRoot());
    std::vector<std::unique_ptr<Node>> owned;
    std::unordered_set<Node*> seen;
    if (clone)
    {
        owned.emplace_back(clone);
        seen.insert(clone);
    }
    for (size_t i = 0; i < owned.size(); ++i)
        for (auto* child : owned[i]->neighbors)
            if (seen.insert(child).second) owned.emplace_back(child);
    std::vector<std::vector<u32>> actual(graph.nodes.size());
    ASSERT_EQ(owned.size(), graph.nodes.size());
    for (auto& node : owned)
    {
        ASSERT_GE(node->val, 1);
        ASSERT_LE(cast<u32>(node->val), actual.size());
        for (auto& original : graph.nodes) ASSERT_NE(node.get(), &original);
        for (auto* child : node->neighbors)
            actual[cast<u32>(node->val - 1)].push_back(cast<u32>(child->val));
    }
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0133_clone_graph,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
