#include "3346.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFrequency;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,11,20,20] 5 1 2

[88,53] 27 2 2
)cases");

using t3346 = SolutionTests<Solution>;

TEST_P(t3346, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxFrequency(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3346,
    t3346::parameters(kCases.size()),
    t3346::name);
