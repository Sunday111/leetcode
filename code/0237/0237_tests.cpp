#include "0237.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<LeetCodeList<ListNode>, int>,
    LeetCodeList<ListNode>>(R"cases(
[4,5,1,9] 5 [4,1,9]
[4,5,1,9] 1 [4,5,9]
)cases");

using t0237 = SolutionTests<Solution>;
TEST_P(t0237, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [list, value] = inputs;
            auto* node = FindFirst(list.head, value);
            ASSERT_NE(node, nullptr);
            ASSERT_NE(node->next, nullptr);
            solution.deleteNode(node);
            ASSERT_EQ(expected, list);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0237,
    t0237::parameters(kCases.size()),
    t0237::name);
