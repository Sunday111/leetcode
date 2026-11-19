#include "0215.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findKthLargest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,5,9999] 1 9999
)cases");

using t0215 = SolutionTests<Solution>;

TEST_P(t0215, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findKthLargest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0215,
    t0215::parameters(kCases.size()),
    t0215::name);
