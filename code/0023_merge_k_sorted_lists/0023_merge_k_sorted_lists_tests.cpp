#include "0023_merge_k_sorted_lists.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<LeetCodeList<ListNode>>>,
    LeetCodeList<ListNode>>(R"cases(
[[1,4,5],[1,3,4],[2,6]] [1,1,2,3,4,4,5,6]
[] []
[[]] []
)cases");

using t0023_merge_k_sorted_lists = SolutionTests<Solution>;
TEST_P(t0023_merge_k_sorted_lists, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [lists] = inputs;
            std::vector<ListNode*> heads;
            for (auto& list : lists) heads.push_back(list.head);
            auto* actual = solution.mergeKLists(heads);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0023_merge_k_sorted_lists,
    t0023_merge_k_sorted_lists::parameters(kCases.size()),
    t0023_merge_k_sorted_lists::name);
