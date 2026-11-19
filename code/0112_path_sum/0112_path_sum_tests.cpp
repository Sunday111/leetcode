#include "0112_path_sum.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<LeetCodeBinaryTree<TreeNode>, int>,
    bool>(R"cases(
[5,4,8,11,null,13,4,7,2,null,null,null,1] 22 true
[1,2,3] 5 false
[null] 0 false
)cases");

class t0112_path_sum : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0112_path_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [tree, sum] = inputs;
    ASSERT_EQ(expected, Solution{}.hasPathSum(tree.root, sum));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0112_path_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
