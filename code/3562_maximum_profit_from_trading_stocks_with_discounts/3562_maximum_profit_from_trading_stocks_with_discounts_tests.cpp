#include "3562_maximum_profit_from_trading_stocks_with_discounts.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxProfit;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 [1,2] [4,3] [[1,2]] 3 5

2 [3,4] [5,8] [[1,2]] 4 4

3 [4,6,8] [7,9,11] [[1,2],[1,3]] 10 10

3 [5,2,3] [8,5,6] [[1,2],[2,3]] 7 12

3 [26,17,11] [40,46,13] [[1,3],[3,2]] 98 60

8 [39,14,15,30,25,16,46,11] [28,47,9,9,33,34,42,24] [[1,2],[2,7],[2,4],[7,6],[7,3],[3,5],[1,8]] 102 116

1 [28] [6] [] 2 0
)cases");

class t3562_maximum_profit_from_trading_stocks_with_discounts
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3562_maximum_profit_from_trading_stocks_with_discounts, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxProfit(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3562_maximum_profit_from_trading_stocks_with_discounts,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
