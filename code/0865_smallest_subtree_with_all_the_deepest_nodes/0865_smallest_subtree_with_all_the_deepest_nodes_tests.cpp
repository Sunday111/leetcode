#include "0865_smallest_subtree_with_all_the_deepest_nodes.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::subtreeWithAllDeepest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,5,1,6,2,0,8,null,null,7,4] [2,7,4]

[1] [1]

[0,1,3,null,2] [2]

[0,2,1,null,null,3] [3]
)cases");

class t0865_smallest_subtree_with_all_the_deepest_nodes
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0865_smallest_subtree_with_all_the_deepest_nodes, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.subtreeWithAllDeepest(args...); },
        inputs);
    ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0865_smallest_subtree_with_all_the_deepest_nodes,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
