#include <algorithm>
#include <vector>

#include "0301_remove_invalid_parentheses.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeInvalidParentheses;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()())()" ["(())()","()()()"]

"))((" [""]

")()(" ["()"]

"((((((((((((((((((aaaaa))" ["((aaaaa))"]

"(((k()((" ["(k)","k()"]

"()(()m)" ["()(()m)"]

"())(((()m)(" ["()(()m)"]
)cases");

using t0301_remove_invalid_parentheses = SolutionTests<Solution>;

TEST_P(t0301_remove_invalid_parentheses, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.removeInvalidParentheses(args...); },
                inputs);
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0301_remove_invalid_parentheses,
    t0301_remove_invalid_parentheses::parameters(kCases.size()),
    t0301_remove_invalid_parentheses::name);
