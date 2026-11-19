#include "3495_minimum_operations_to_make_array_zero.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[2,4]] 3
)cases");

using t3495_minimum_operations_to_make_array_zero = SolutionTests<Solution>;

TEST_P(t3495_minimum_operations_to_make_array_zero, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3495_minimum_operations_to_make_array_zero,
    t3495_minimum_operations_to_make_array_zero::parameters(kCases.size()),
    t3495_minimum_operations_to_make_array_zero::name);
