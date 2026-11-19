#include "3623.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countTrapezoids;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,0],[2,0],[3,0],[2,2],[3,2]] 3
)cases");

using t3623 = SolutionTests<Solution>;

TEST_P(t3623, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countTrapezoids(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3623,
    t3623::parameters(kCases.size()),
    t3623::name);
