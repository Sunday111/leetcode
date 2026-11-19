#include "2147_number_of_ways_to_divide_a_long_corridor.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"SSPPSPS" 3

"PPSPSP" 1

"S" 0

"P" 0
)cases");

using t2147_number_of_ways_to_divide_a_long_corridor = SolutionTests<Solution>;

TEST_P(t2147_number_of_ways_to_divide_a_long_corridor, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2147_number_of_ways_to_divide_a_long_corridor,
    t2147_number_of_ways_to_divide_a_long_corridor::parameters(kCases.size()),
    t2147_number_of_ways_to_divide_a_long_corridor::name);
