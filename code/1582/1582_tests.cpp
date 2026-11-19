#include "1582_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1582_special_positions_in_a_binary_matrix = SolutionTests<Solution>;

TEST_P(t1582_special_positions_in_a_binary_matrix, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numSpecial(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1582_special_positions_in_a_binary_matrix,
    t1582_special_positions_in_a_binary_matrix::parameters(kCases.size()),
    t1582_special_positions_in_a_binary_matrix::name);
