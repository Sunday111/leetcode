#include "0132_palindrome_partitioning_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCut;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbab" 1
)cases");

using t0132_palindrome_partitioning_2 = SolutionTests<Solution>;

TEST_P(t0132_palindrome_partitioning_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.minCut(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0132_palindrome_partitioning_2,
    t0132_palindrome_partitioning_2::parameters(kCases.size()),
    t0132_palindrome_partitioning_2::name);
