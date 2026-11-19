#include <print>

#include "0166_fraction_to_recurring_decimal.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fractionToDecimal;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 333 "0.(012)"

1 2 "0.5"
)cases");

class t0166_fraction_to_recurring_decimal
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0166_fraction_to_recurring_decimal, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.fractionToDecimal(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0166_fraction_to_recurring_decimal,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
