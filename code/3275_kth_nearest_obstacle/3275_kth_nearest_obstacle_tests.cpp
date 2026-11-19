#include "3275_kth_nearest_obstacle.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::resultsArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3,4],[2,3],[-3,0]] 2 [-1,7,5,3]
)cases");

using t3275_kth_nearest_obstacle = SolutionTests<Solution>;

TEST_P(t3275_kth_nearest_obstacle, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.resultsArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3275_kth_nearest_obstacle,
    t3275_kth_nearest_obstacle::parameters(kCases.size()),
    t3275_kth_nearest_obstacle::name);
