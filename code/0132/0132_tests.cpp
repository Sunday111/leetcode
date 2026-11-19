#include "0132.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCut;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbab" 1
)cases");

using t0132 = SolutionTests<Solution>;

TEST_P(t0132, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.minCut(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0132,
    t0132::parameters(kCases.size()),
    t0132::name);
