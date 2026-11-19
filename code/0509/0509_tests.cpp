#include "0509.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fib;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
0 0

1 1

2 1

3 2

4 3
)cases");

using t0509 = SolutionTests<Solution>;

TEST_P(t0509, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.fib(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0509,
    t0509::parameters(kCases.size()),
    t0509::name);
