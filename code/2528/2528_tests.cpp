#include "2528.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPower;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,4,4] 0 3 4
)cases");

using t2528 = SolutionTests<Solution>;

TEST_P(t2528, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxPower(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2528,
    t2528::parameters(kCases.size()),
    t2528::name);
