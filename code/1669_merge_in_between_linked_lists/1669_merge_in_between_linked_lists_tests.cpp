#include "1669_merge_in_between_linked_lists.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::mergeInBetween;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,1,13,6,9,5] 3 4 [1000000,1000001,1000002] [10,1,13,1000000,1000001,1000002,5]

[0,1,2,3,4,5,6] 2 5 [1000000,1000001,1000002,1000003,1000004] [0,1,1000000,1000001,1000002,1000003,1000004,6]
)cases");

using t1669_merge_in_between_linked_lists = SolutionTests<Solution>;

TEST_P(t1669_merge_in_between_linked_lists, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mergeInBetween(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1669_merge_in_between_linked_lists,
    t1669_merge_in_between_linked_lists::parameters(kCases.size()),
    t1669_merge_in_between_linked_lists::name);
