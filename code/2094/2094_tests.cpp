#include "2094.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findEvenNumbers;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] [132,312]

[2,1,3,0] [102,120,130,132,210,230,302,310,312,320]

[2,2,8,8,2] [222,228,282,288,822,828,882]

[3,7,5] []
)cases");

using t2094 = SolutionTests<Solution>;

TEST_P(t2094, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findEvenNumbers(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2094,
    t2094::parameters(kCases.size()),
    t2094::name);
