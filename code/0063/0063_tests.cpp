#include "0063.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::uniquePathsWithObstacles;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,0],[0,1,0],[0,0,0]] 2

[[0,1],[0,0]] 1

[[1,0]] 0
)cases");

using t0063 = SolutionTests<Solution>;

TEST_P(t0063, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.uniquePathsWithObstacles(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0063,
    t0063::parameters(kCases.size()),
    t0063::name);
