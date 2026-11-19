#include "2427.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::commonFactors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
12 6 4

25 30 2
)cases");

using t2427 = SolutionTests<Solution>;

TEST_P(t2427, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.commonFactors(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2427,
    t2427::parameters(kCases.size()),
    t2427::name);
