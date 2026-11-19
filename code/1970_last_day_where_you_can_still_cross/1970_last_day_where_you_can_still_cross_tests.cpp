#include "1970_last_day_where_you_can_still_cross.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::latestDayToCross;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 2 [[1,1],[2,1],[1,2],[2,2]] 2
)cases");

using t1970_last_day_where_you_can_still_cross = SolutionTests<Solution>;

TEST_P(t1970_last_day_where_you_can_still_cross, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.latestDayToCross(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1970_last_day_where_you_can_still_cross,
    t1970_last_day_where_you_can_still_cross::parameters(kCases.size()),
    t1970_last_day_where_you_can_still_cross::name);
