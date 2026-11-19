#include "0237_delete_node_in_a_linked_list.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<LeetCodeList<ListNode>, int>,
    LeetCodeList<ListNode>>(R"cases(
[4,5,1,9] 5 [4,1,9]
[4,5,1,9] 1 [4,5,9]
)cases");

class t0237_delete_node_in_a_linked_list
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0237_delete_node_in_a_linked_list, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [list, value] = inputs;
    auto* node = FindFirst(list.head, value);
    ASSERT_NE(node, nullptr);
    ASSERT_NE(node->next, nullptr);
    Solution{}.deleteNode(node);
    ASSERT_EQ(expected, list);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0237_delete_node_in_a_linked_list,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
