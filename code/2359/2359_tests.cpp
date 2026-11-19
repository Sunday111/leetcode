#include "2359.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::closestMeetingNode;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,8,-1,9,8,4,4,1,1] 5 6 1
)cases");

using t2359 = SolutionTests<Solution>;

TEST_P(t2359, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.closestMeetingNode(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2359,
    t2359::parameters(kCases.size()),
    t2359::name);
