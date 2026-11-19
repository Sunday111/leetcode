#include "3625_alt_5.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countTrapezoids;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0],[1,0],[0,1],[2,1]] 1

[[-3,2],[3,0],[2,3],[3,2],[2,-3]] 2

[[71,-89],[-75,-89],[-9,11],[-24,-89],[-51,-89],[-77,-89],[42,11]] 10
)cases");

using t3625 = SolutionTests<Solution>;

TEST_P(t3625, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countTrapezoids(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3625,
    t3625::parameters(kCases.size()),
    t3625::name);
