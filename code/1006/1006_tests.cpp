#include "1006.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::clumsy;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 7

10 12
)cases");

using t1006 = SolutionTests<Solution>;

TEST_P(t1006, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.clumsy(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1006,
    t1006::parameters(kCases.size()),
    t1006::name);
