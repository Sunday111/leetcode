#include "0022_generate_parentheses.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint8_t>, std::vector<std::string>>(
        R"cases(
3 ["((()))","(()())","(())()","()(())","()()()"]
1 ["()"]
)cases");

using t0022_generate_parentheses = SolutionTests<Solution>;
TEST_P(t0022_generate_parentheses, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = solution.generateParenthesis(std::get<0>(inputs));
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0022_generate_parentheses,
    t0022_generate_parentheses::parameters(kCases.size()),
    t0022_generate_parentheses::name);
