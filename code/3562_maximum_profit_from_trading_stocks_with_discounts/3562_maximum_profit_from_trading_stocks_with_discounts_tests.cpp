#include "3562_maximum_profit_from_trading_stocks_with_discounts.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_1)
{
    u8 n = 2;
    std::vector present{1, 2};
    std::vector future{4, 3};
    auto hierarchy = parse2DArray("[[1,2]]");
    u8 budget = 3;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 5);
}

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_2)
{
    u8 n = 2;
    std::vector present{3, 4};
    std::vector future{5, 8};
    auto hierarchy = parse2DArray("[[1,2]]");
    u8 budget = 4;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 4);
}

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_3)
{
    u8 n = 3;
    std::vector present{4, 6, 8};
    std::vector future{7, 9, 11};
    auto hierarchy = parse2DArray("[[1,2],[1,3]]");
    u8 budget = 10;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 10);
}

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_4)
{
    u8 n = 3;
    std::vector present{5, 2, 3};
    std::vector future{8, 5, 6};
    auto hierarchy = parse2DArray("[[1,2],[2,3]]");
    u8 budget = 7;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 12);
}

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_5)
{
    u8 n = 3;
    std::vector present{26, 17, 11};
    std::vector future{40, 46, 13};
    auto hierarchy = parse2DArray("[[1,3],[3,2]]");
    u8 budget = 98;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 60);
}

TEST(t3562_maximum_profit_from_trading_stocks_with_discounts, test_6)
{
    u8 n = 8;
    std::vector present{39, 14, 15, 30, 25, 16, 46, 11};
    std::vector future{28, 47, 9, 9, 33, 34, 42, 24};
    auto hierarchy =
        parse2DArray("[[1,2],[2,7],[2,4],[7,6],[7,3],[3,5],[1,8]]");
    u8 budget = 102;
    ASSERT_EQ(Solution{}.maxProfit(n, present, future, hierarchy, budget), 116);
}
