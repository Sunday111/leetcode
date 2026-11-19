#include "0735.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::asteroidCollision;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,2,-5] [10]

[-2,-1,1,2] [-2,-1,1,2]
)cases");

using t0735 = SolutionTests<Solution>;

TEST_P(t0735, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.asteroidCollision(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0735,
    t0735::parameters(kCases.size()),
    t0735::name);
