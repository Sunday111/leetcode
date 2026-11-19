#include "0054.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spiralOrder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,3],[4,5,6],[7,8,9]] [1,2,3,6,9,8,7,4,5]
)cases");

using t0054 = SolutionTests<Solution>;

TEST_P(t0054, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.spiralOrder(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0054,
    t0054::parameters(kCases.size()),
    t0054::name);
