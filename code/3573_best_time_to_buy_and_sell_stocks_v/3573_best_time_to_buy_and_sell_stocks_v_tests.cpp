#include "3573_best_time_to_buy_and_sell_stocks_v.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumProfit;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,7,9,8,2] 2 14

[12,16,19,19,8,1,19,13,9] 3 36
)cases");

class t3573_best_time_to_buy_and_sell_stocks_v
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3573_best_time_to_buy_and_sell_stocks_v, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maximumProfit(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3573_best_time_to_buy_and_sell_stocks_v,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
