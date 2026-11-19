#include "2654.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[6,10,15] 4

[2,6,3,4] 4
)cases");

using t2654 = SolutionTests<Solution>;

TEST_P(t2654, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2654,
    t2654::parameters(kCases.size()),
    t2654::name);
