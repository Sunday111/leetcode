#include "3454_separate_squares_ii.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::separateSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,1],[2,2,1]] 1

[[0,0,2],[1,1,1]] 1

[[15,21,2],[19,21,3]] 22.3
)cases");

using t3454_separate_squares_ii = SolutionTests<Solution>;

TEST_P(t3454_separate_squares_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.separateSquares(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3454_separate_squares_ii,
    t3454_separate_squares_ii::parameters(kCases.size()),
    t3454_separate_squares_ii::name);
