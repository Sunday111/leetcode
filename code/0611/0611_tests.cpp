#include "0611.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::triangleNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,2,3,4] 3

[1,1,3,4] 0

[0,2,2] 0

[2,3,4,4] 4
)cases");

using t0611 = SolutionTests<Solution>;

TEST_P(t0611, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.triangleNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0611,
    t0611::parameters(kCases.size()),
    t0611::name);
