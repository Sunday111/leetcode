#include "1536_minimum_swaps_to_arrange_a_binary_gridtest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1536_minimum_swaps_to_arrange_a_binary_grid = SolutionTests<Solution>;

TEST_P(t1536_minimum_swaps_to_arrange_a_binary_grid, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSwaps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1536_minimum_swaps_to_arrange_a_binary_grid,
    t1536_minimum_swaps_to_arrange_a_binary_grid::parameters(kCases.size()),
    t1536_minimum_swaps_to_arrange_a_binary_grid::name);
