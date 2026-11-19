#include "2141_maximum_running_time_of_n_computers.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRunTime;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [10,10,3,5] 8
)cases");

using t2141_maximum_running_time_of_n_computers = SolutionTests<Solution>;

TEST_P(t2141_maximum_running_time_of_n_computers, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRunTime(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2141_maximum_running_time_of_n_computers,
    t2141_maximum_running_time_of_n_computers::parameters(kCases.size()),
    t2141_maximum_running_time_of_n_computers::name);
