#include "0024_swap_nodes_in_pairs.hpp"
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::swapPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4] [2,1,4,3]
)");

using t0024_swap_nodes_in_pairs = SolutionTests<Solution>;

TEST_P(t0024_swap_nodes_in_pairs, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.swapPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0024_swap_nodes_in_pairs,
    t0024_swap_nodes_in_pairs::parameters(kCases.size()),
    t0024_swap_nodes_in_pairs::name);
