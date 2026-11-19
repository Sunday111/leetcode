#include "3798_largest_even_number.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestEven;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1112" "1112"

"111" ""
)cases");

using t3798_largest_even_number = SolutionTests<Solution>;

TEST_P(t3798_largest_even_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestEven(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3798_largest_even_number,
    t3798_largest_even_number::parameters(kCases.size()),
    t3798_largest_even_number::name);
