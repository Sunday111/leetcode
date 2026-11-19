#include <algorithm>
#include <vector>

#include "0301_remove_invalid_parentheses.hpp"
#include "gtest/gtest.h"
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

class t0301_remove_invalid_parentheses : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0301_remove_invalid_parentheses, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.removeInvalidParentheses(args...); },
        inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0301_remove_invalid_parentheses,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
