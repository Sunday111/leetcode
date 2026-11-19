#include "3355_zero_array_transformations_1.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isZeroArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,0,1] [[0,2]] true

[4,6] [[0,0],[0,0],[0,0],[0,0],[0,0],[0,1],[0,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1],[1,1]] true

[0,3,9] [[0,2],[0,2],[1,1],[1,2],[1,2],[2,2]] false

[1,1,3] [[0,0],[0,0],[0,0],[0,1],[0,2],[0,2],[1,1],[1,1],[1,1],[1,1],[2,2],[2,2]] true
)cases");

using t3355_zero_array_transformations_1 = SolutionTests<Solution>;

TEST_P(t3355_zero_array_transformations_1, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isZeroArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3355_zero_array_transformations_1,
    t3355_zero_array_transformations_1::parameters(kCases.size()),
    t3355_zero_array_transformations_1::name);
