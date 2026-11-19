#include "2322_minimum_score_after_removals_on_a_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumScore;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,5,2,4,4,2] [[0,1],[1,2],[5,2],[4,3],[1,3]] 0

[1,5,5,4,11] [[0,1],[1,2],[1,3],[3,4]] 9
)cases");

using t2322_minimum_score_after_removals_on_a_tree = SolutionTests<Solution>;

TEST_P(t2322_minimum_score_after_removals_on_a_tree, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumScore(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2322_minimum_score_after_removals_on_a_tree,
    t2322_minimum_score_after_removals_on_a_tree::parameters(kCases.size()),
    t2322_minimum_score_after_removals_on_a_tree::name);
