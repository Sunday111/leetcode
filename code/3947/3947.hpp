// https://leetcode.com/problems/maximum-number-of-items-from-sale-ii/

#include <algorithm>
#include <cassert>
#include <vector>

#include "integral_aliases.hpp"
#include "math/precompute_primes.hpp"
#include "minmax/min2.hpp"
#include "radix_sort/adaptive_sort.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

inline static constexpr u32 M = 100'000;
inline static constexpr auto g_primes = precompute_primes<M>();

class LC_SOLUTION_NAME()
{
public:
    inline static u32 counts[M + 1];
    inline static u64 sorted[M];

    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 impl(const std::vector<std::vector<u32>>& items, u32 budget)
    {
        const auto n = static_cast<u32>(items.size());
        std::fill_n(counts, n + 1, 0u);

        u32 min_price = 1'000'000'000;

        for (auto& item : items)
        {
            u32 factor = item[0];
            u32 price = item[1];
            min_price = min2(min_price, price);
            ++counts[factor];
        }

        for (const u32 p : g_primes.data)
        {
            assert(p >= 2);
            if (p > n) break;
            for (u32 i = n / p; i >= 1; --i)
            {
                u32 next = i * p;
                counts[i] += counts[next];
            }
        }

        u32 num_sorted = 0;
        u32 offset_bits = 0;
        for (auto& item : items)
        {
            u32 factor = item[0];
            u32 price = item[1];

            const u32 free_items = counts[factor] - 1;
            const u32 offset = price - min_price;
            sorted[num_sorted] = (u64{offset} << 32) | free_items;
            num_sorted += free_items != 0;
            offset_bits |= offset;
        }

        adaptive_sort<32, M, 32>(sorted, num_sorted, offset_bits);

        u32 answer = 0;

        for (u32 i = 0; i != num_sorted; ++i)
        {
            const u32 price = (sorted[i] >> 32) + min_price;
            const u32 free_items = sorted[i] & ~u32{};
            u32 can_buy = min2(budget / price, free_items);

            if (!can_buy)
            {
                break;
            }

            if (2 * can_buy + (budget - can_buy * price) / min_price <
                budget / min_price)
            {
                break;
            }

            answer += 2 * can_buy;
            budget -= can_buy * price;
        }

        answer += budget / min_price;

        return answer;
    }

    static u32 maximumSaleItems(
        const std::vector<std::vector<int>>& items,
        u32 budget) noexcept
    {
        return impl(
            reinterpret_cast<const std::vector<std::vector<u32>>&>(items),
            budget);
    }
};
