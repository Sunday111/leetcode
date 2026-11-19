#include "1006_clumsy_factorial.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::clumsy;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 7

10 12
)cases");

using t1006_clumsy_factorial = SolutionTests<Solution>;

TEST_P(t1006_clumsy_factorial, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.clumsy(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1006_clumsy_factorial,
    t1006_clumsy_factorial::parameters(kCases.size()),
    t1006_clumsy_factorial::name);
