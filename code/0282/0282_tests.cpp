#include <algorithm>

#include "0282.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addOperators;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"123" 6 ["1*2*3","1+2+3"]

"232" 8 ["2*3+2","2+3*2"]

"3456237490" 9191 []

"105" 5 ["1*0+5","10-5"]
)cases");

using t0282_expression_add_operators = SolutionTests<Solution>;

TEST_P(t0282_expression_add_operators, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.addOperators(args...); },
                inputs);
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0282_expression_add_operators,
    t0282_expression_add_operators::parameters(kCases.size()),
    t0282_expression_add_operators::name);
