#include "1503.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLastMoment;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 [4,3] [0,1] 4
)cases");

using t1503_last_momemnt_before_all_ants_fall_out_of_a_plank =
    SolutionTests<Solution>;

TEST_P(t1503_last_momemnt_before_all_ants_fall_out_of_a_plank, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLastMoment(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1503_last_momemnt_before_all_ants_fall_out_of_a_plank,
    t1503_last_momemnt_before_all_ants_fall_out_of_a_plank::parameters(
        kCases.size()),
    t1503_last_momemnt_before_all_ants_fall_out_of_a_plank::name);
