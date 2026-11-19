#include "2943_maximize_area_of_square_hole_in_grid.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximizeSquareHoleArea;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 1 [2,3] [2] 4

1 1 [2] [2] 4

3 2 [3,2,4] [3,2] 9

4 40 [5,3,2,4] [36,41,6,34,33] 9
)cases");

using t2943_maximize_area_of_square_hole_in_grid = SolutionTests<Solution>;

TEST_P(t2943_maximize_area_of_square_hole_in_grid, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximizeSquareHoleArea(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2943_maximize_area_of_square_hole_in_grid,
    t2943_maximize_area_of_square_hole_in_grid::parameters(kCases.size()),
    t2943_maximize_area_of_square_hole_in_grid::name);
