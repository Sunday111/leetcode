#include "1700.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countStudents;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1] [0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0] 3
)cases");

using t1700 = SolutionTests<Solution>;

TEST_P(t1700, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countStudents(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1700,
    t1700::parameters(kCases.size()),
    t1700::name);
