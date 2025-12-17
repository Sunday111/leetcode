#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    static constexpr i64 maximumProfit(std::vector<int>& prices, u32 k) noexcept
    {
        i64 min_price = prices.front();
        i64 max_price = min_price;
        size_t min_day = 0;
        size_t max_day = 0;

        // max_profit[i] is max profit from all transactions
        // happened before the day i
        std::vector<i64> max_profit(prices.size() + 1, 0);
        max_profit[0] = 0;

        for (size_t i = 1; i != prices.size(); ++i)
        {
            i64 price = prices[i];

            i64 normal_deal = max_profit[min_day] + price - min_price;
            i64 short_deal = max_profit[max_day] + max_price - price;
            max_profit[i] =
                std::max({normal_deal, short_deal, max_profit[i - 1]});

            max_price = std::max(max_price, price);
            min_price = std::min(min_price, price);

            if (min_price == price) min_day = i;
            if (max_price == price) max_day = i;
        }

        return prices.back();
    }
};
