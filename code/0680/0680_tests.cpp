#include "0680.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, bool>(R"cases(
"cupuuffuupucu" true
"deeee" true
)cases");

using t0680_valid_palindrome = SolutionTests<Solution>;
TEST_P(t0680_valid_palindrome, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            ASSERT_EQ(expected, solution.validPalindrome(std::get<0>(inputs)));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0680_valid_palindrome,
    t0680_valid_palindrome::parameters(kCases.size()),
    t0680_valid_palindrome::name);
