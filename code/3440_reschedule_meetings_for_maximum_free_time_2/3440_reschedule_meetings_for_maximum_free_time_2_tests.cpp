#include "3440_reschedule_meetings_for_maximum_free_time_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFreeTime;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 [1,3] [2,5] 2

37 [5,14,27,34] [13,18,31,37] 16

20 [2,4,6,9,18] [4,6,9,16,20] 4
)cases");

using t3440_reschedule_meetings_for_maximum_free_time_2 =
    SolutionTests<Solution>;

TEST_P(t3440_reschedule_meetings_for_maximum_free_time_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxFreeTime(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3440_reschedule_meetings_for_maximum_free_time_2,
    t3440_reschedule_meetings_for_maximum_free_time_2::parameters(
        kCases.size()),
    t3440_reschedule_meetings_for_maximum_free_time_2::name);
