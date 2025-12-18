#include <algorithm>
#include <cstdint>
#include <span>

class Solution
{
public:
    using u32 = uint32_t;
    using i64 = int64_t;
    static constexpr i64
    maxProfit(std::span<const int> p, std::span<const int> s, u32 k) noexcept
    {
        const u32 n = static_cast<u32>(p.size()), k2 = k / 2;
        i64 sk = 0;
        // sk - profit sum over last k, original strategy
        for (u32 i = 0; i != k2; ++i)
        {
            sk += i64{p[i]} * i64{s[i]};
        }

        // sk - profit sum over last k, new strategy (sum of last k2)
        i64 sk2 = 0;
        for (u32 i = k2; i != k; ++i)
        {
            sk += i64{p[i]} * i64{s[i]};
            sk2 += i64{p[i]};
        }

        i64 total = sk, d = sk2 - sk;
        for (u32 left = 0, mid = k2, right = k; right != n;
             ++left, ++mid, ++right)
        {
            i64 ith_profit = i64{p[right]} * i64{s[right]};
            total += ith_profit;
            sk += ith_profit - i64{p[left]} * i64{s[left]};
            sk2 += i64{p[right]} - i64{p[mid]};
            d = std::max(d, sk2 - sk);
        }

        return total + std::max<i64>(0, d);
    }
};
