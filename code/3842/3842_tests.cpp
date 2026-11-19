#include "3842.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::toggleLightBulbs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,30,20,10] [20,30]

[100,100] []
)cases");

using t3842 = SolutionTests<Solution>;

TEST_P(t3842, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.toggleLightBulbs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3842,
    t3842::parameters(kCases.size()),
    t3842::name);
