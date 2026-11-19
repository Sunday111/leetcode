#include "1970.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::latestDayToCross;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 2 [[1,1],[2,1],[1,2],[2,2]] 2
)cases");

using t1970 = SolutionTests<Solution>;

TEST_P(t1970, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.latestDayToCross(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1970,
    t1970::parameters(kCases.size()),
    t1970::name);
