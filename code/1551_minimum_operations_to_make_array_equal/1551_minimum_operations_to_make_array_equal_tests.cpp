#include "1551_minimum_operations_to_make_array_equaltest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1551_minimum_operations_to_make_array_equal = SolutionTests<Solution>;

TEST_P(t1551_minimum_operations_to_make_array_equal, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1551_minimum_operations_to_make_array_equal,
    t1551_minimum_operations_to_make_array_equal::parameters(kCases.size()),
    t1551_minimum_operations_to_make_array_equal::name);
