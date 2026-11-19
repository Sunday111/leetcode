#include "0043.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::string>(R"cases(
"0" "1009" "0"
"2" "3" "6"
"123" "456" "56088"
"99" "99" "9801"
)cases");

using t0043_multiply_strings = SolutionTests<Solution>;
TEST_P(t0043_multiply_strings, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [a, b] = inputs;
            ASSERT_EQ(expected, solution.multiply(a, b));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0043_multiply_strings,
    t0043_multiply_strings::parameters(kCases.size()),
    t0043_multiply_strings::name);
