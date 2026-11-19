#include <cassert>

#include "0019.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeNthFromEnd;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4,5] 2 [1,2,3,5]
)");

using t0019_remove_nth_node_from_end_of_list = SolutionTests<Solution>;

TEST_P(t0019_remove_nth_node_from_end_of_list, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.removeNthFromEnd(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0019_remove_nth_node_from_end_of_list,
    t0019_remove_nth_node_from_end_of_list::parameters(kCases.size()),
    t0019_remove_nth_node_from_end_of_list::name);
