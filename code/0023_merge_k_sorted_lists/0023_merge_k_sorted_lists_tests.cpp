#include "0023_merge_k_sorted_lists.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<LeetCodeList<ListNode>>>,
    LeetCodeList<ListNode>>(R"cases(
[[1,4,5],[1,3,4],[2,6]] [1,1,2,3,4,4,5,6]
[] []
[[]] []
)cases");

class t0023_merge_k_sorted_lists : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0023_merge_k_sorted_lists, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [lists] = inputs;
    std::vector<ListNode*> heads;
    for (auto& list : lists) heads.push_back(list.head);
    auto* actual = Solution{}.mergeKLists(heads);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0023_merge_k_sorted_lists,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
