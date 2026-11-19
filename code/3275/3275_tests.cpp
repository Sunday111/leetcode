#include "3275.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::resultsArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3,4],[2,3],[-3,0]] 2 [-1,7,5,3]
)cases");

using t3275 = SolutionTests<Solution>;

TEST_P(t3275, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.resultsArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3275,
    t3275::parameters(kCases.size()),
    t3275::name);
