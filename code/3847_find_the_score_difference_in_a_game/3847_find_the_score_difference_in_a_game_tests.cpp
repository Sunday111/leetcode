#include "3847_find_the_score_difference_in_a_game.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::scoreDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 0

[2,4,2,1,2,1] 4

[1] -1
)cases");

using t3847_find_the_score_difference_in_a_game = SolutionTests<Solution>;

TEST_P(t3847_find_the_score_difference_in_a_game, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.scoreDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3847_find_the_score_difference_in_a_game,
    t3847_find_the_score_difference_in_a_game::parameters(kCases.size()),
    t3847_find_the_score_difference_in_a_game::name);
