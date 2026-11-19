#include "1605_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1605_find_valid_matrix_given_row_and_column_sums =
    SolutionTests<Solution>;

TEST_P(t1605_find_valid_matrix_given_row_and_column_sums, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.restoreMatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1605_find_valid_matrix_given_row_and_column_sums,
    t1605_find_valid_matrix_given_row_and_column_sums::parameters(
        kCases.size()),
    t1605_find_valid_matrix_given_row_and_column_sums::name);
