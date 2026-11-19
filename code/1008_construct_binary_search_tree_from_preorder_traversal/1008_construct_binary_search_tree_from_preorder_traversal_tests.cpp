#include "1008_construct_binary_search_tree_from_preorder_traversal.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::bstFromPreorder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[8,5,1,7,10,12] [8,5,10,1,7,null,12]
)cases");

class t1008_construct_binary_search_tree_from_preorder_traversal
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1008_construct_binary_search_tree_from_preorder_traversal, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.bstFromPreorder(args...); },
        inputs);
    const bool equal = CompareBinaryTrees(expected.root, actual);
    DeleteBinaryTree(actual);
    ASSERT_TRUE(equal);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1008_construct_binary_search_tree_from_preorder_traversal,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
