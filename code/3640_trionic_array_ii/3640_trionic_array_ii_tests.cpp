#include "3640_trionic_array_ii.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSumTrionic;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,-2,-1,-3,0,2,-1] -4

[1,4,2,7] 14
)cases");

using t3640_trionic_array_ii = SolutionTests<Solution>;

TEST_P(t3640_trionic_array_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSumTrionic(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3640_trionic_array_ii,
    t3640_trionic_array_ii::parameters(kCases.size()),
    t3640_trionic_array_ii::name);
