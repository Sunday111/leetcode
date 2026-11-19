#include "3419.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minMaxWeight;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]] 2 1
)cases");

using t3419 = SolutionTests<Solution>;

TEST_P(t3419, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minMaxWeight(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3419,
    t3419::parameters(kCases.size()),
    t3419::name);
