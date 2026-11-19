#include <algorithm>

#include "0282_expression_add_operators.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addOperators;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"123" 6 ["1*2*3","1+2+3"]

"232" 8 ["2*3+2","2+3*2"]

"3456237490" 9191 []

"105" 5 ["1*0+5","10-5"]
)cases");

class t0282_expression_add_operators : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0282_expression_add_operators, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.addOperators(args...); },
        inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0282_expression_add_operators,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
