#include "3362_zero_array_transformation_3.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,0,2] [[0,2],[0,2],[1,1]] 1

[1,2,3,4] [[0,3]] -1

[0,3] [[0,0],[0,0],[0,1],[0,1],[0,1]] 2
)cases");

using t3362_zero_array_transformation_3 = SolutionTests<Solution>;

TEST_P(t3362_zero_array_transformation_3, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3362_zero_array_transformation_3,
    t3362_zero_array_transformation_3::parameters(kCases.size()),
    t3362_zero_array_transformation_3::name);
