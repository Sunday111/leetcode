#include <print>

#include "0407.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::trapRainWater;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] 4
)cases");

using t0407 = SolutionTests<Solution>;

TEST_P(t0407, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.trapRainWater(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0407,
    t0407::parameters(kCases.size()),
    t0407::name);
