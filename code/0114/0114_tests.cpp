#include <array>
#include <cstddef>
#include <string_view>
#include <vector>

#include "0114.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::vector<size_t>>(
        R"cases(
"null" []
"0" [0]
"1,2,5,3,4,null,6" [0,1,3,4,2,5]
"1,2" [0,1]
"1,2,null,3" [0,1,2]
"1,null,2,null,3" [0,1,2]
"1,null,2,3" [0,1,2]
"1,1,1,1,1" [0,1,3,4,2]
)cases");

class t0114 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0114, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto tree = LeetCodeBinaryTree<TreeNode>::FromString(std::get<0>(inputs));
    Solution{}.flatten(tree.root);
    auto* node = tree.root;
    for (auto index : expected)
    {
        ASSERT_EQ(node, &tree.nodes[index]);
        ASSERT_EQ(node->left, nullptr);
        node = node->right;
    }
    ASSERT_EQ(node, nullptr);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0114,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
