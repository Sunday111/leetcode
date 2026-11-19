#include "1838.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFrequency;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,4,8,13] 5 2
)cases");

using t1838 = SolutionTests<Solution>;

TEST_P(t1838, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxFrequency(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1838,
    t1838::parameters(kCases.size()),
    t1838::name);
