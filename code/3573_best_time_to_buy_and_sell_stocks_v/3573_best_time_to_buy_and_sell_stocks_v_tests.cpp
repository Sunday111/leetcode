#include "3573_best_time_to_buy_and_sell_stocks_v.hpp"
#include "gtest/gtest.h"

TEST(t3573_best_time_to_buy_and_sell_stocks_v, test_1)
{
    std::vector prices{1, 7, 9, 8, 2};
    ASSERT_EQ(Solution{}.maximumProfit(prices, 2), 14);
}

TEST(t3573_best_time_to_buy_and_sell_stocks_v, test_2)
{
    std::vector prices{12, 16, 19, 19, 8, 1, 19, 13, 9};
    ASSERT_EQ(Solution{}.maximumProfit(prices, 3), 36);
}
