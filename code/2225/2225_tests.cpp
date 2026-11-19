#include "2225.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findWinners;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]] [[1,2,10],[4,5,7,8]]

[[2,3],[1,3],[5,4],[6,4]] [[1,2,5,6],[]]
)cases");

using t2225_find_players_with_zero_or_one_losses = SolutionTests<Solution>;

TEST_P(t2225_find_players_with_zero_or_one_losses, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findWinners(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2225_find_players_with_zero_or_one_losses,
    t2225_find_players_with_zero_or_one_losses::parameters(kCases.size()),
    t2225_find_players_with_zero_or_one_losses::name);
