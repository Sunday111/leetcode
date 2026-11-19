#include "1931.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int, int>, int>(R"cases(
3 1 12

3 2 54

3 3 246
)cases");

using t1931_painting_a_grid_with_tree_different_colors =
    SolutionTests<Solution>;

TEST_P(t1931_painting_a_grid_with_tree_different_colors, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.colorTheGrid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1931_painting_a_grid_with_tree_different_colors,
    t1931_painting_a_grid_with_tree_different_colors::parameters(kCases.size()),
    t1931_painting_a_grid_with_tree_different_colors::name);
