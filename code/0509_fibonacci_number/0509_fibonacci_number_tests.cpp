#include "0509_fibonacci_number.hpp"
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

using t0509_fibonacci_number = SolutionTests<Solution>;

TEST_P(t0509_fibonacci_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.fib(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0509_fibonacci_number,
    t0509_fibonacci_number::parameters(kCases.size()),
    t0509_fibonacci_number::name);
