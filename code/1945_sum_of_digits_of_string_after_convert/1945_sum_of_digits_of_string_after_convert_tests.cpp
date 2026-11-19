#include "1945_sum_of_digits_of_string_after_convert.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLucky;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"iiii" 1 36
)cases");

using t1945_sum_of_digits_of_string_after_convert = SolutionTests<Solution>;

TEST_P(t1945_sum_of_digits_of_string_after_convert, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLucky(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1945_sum_of_digits_of_string_after_convert,
    t1945_sum_of_digits_of_string_after_convert::parameters(kCases.size()),
    t1945_sum_of_digits_of_string_after_convert::name);
