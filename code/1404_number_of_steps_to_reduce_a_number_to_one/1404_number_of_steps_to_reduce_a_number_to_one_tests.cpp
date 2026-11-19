#include "1404_number_of_steps_to_reduce_a_number_to_one.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numSteps;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1101" 6

"11000" 6

"10" 1
)cases");

using t1404_number_of_steps_to_reduce_a_number_to_one = SolutionTests<Solution>;

TEST_P(t1404_number_of_steps_to_reduce_a_number_to_one, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numSteps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1404_number_of_steps_to_reduce_a_number_to_one,
    t1404_number_of_steps_to_reduce_a_number_to_one::parameters(kCases.size()),
    t1404_number_of_steps_to_reduce_a_number_to_one::name);
