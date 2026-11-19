#include "1411_num_of_ways.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 12

5000 30228214
)cases");

using t1411_num_of_ways = SolutionTests<Solution>;

TEST_P(t1411_num_of_ways, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numOfWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1411_num_of_ways,
    t1411_num_of_ways::parameters(kCases.size()),
    t1411_num_of_ways::name);
