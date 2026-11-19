#include "1137_nth_tribonacci_number.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::tribonacci;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 4

25 1389537
)cases");

using t1137_nth_tribonacci_number = SolutionTests<Solution>;

TEST_P(t1137_nth_tribonacci_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.tribonacci(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1137_nth_tribonacci_number,
    t1137_nth_tribonacci_number::parameters(kCases.size()),
    t1137_nth_tribonacci_number::name);
