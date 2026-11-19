#include "2141.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRunTime;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [10,10,3,5] 8
)cases");

using t2141 = SolutionTests<Solution>;

TEST_P(t2141, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRunTime(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2141,
    t2141::parameters(kCases.size()),
    t2141::name);
