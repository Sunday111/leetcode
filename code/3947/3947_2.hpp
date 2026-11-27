// https://leetcode.com/problems/maximum-number-of-items-from-sale-ii/

#include <algorithm>
#include <cassert>
#include <vector>

#include "integral_aliases.hpp"
#include "math/precompute_primes.hpp"
#include "minmax/max2.hpp"
#include "minmax/min2.hpp"
#include "radix_sort/adaptive_sort.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

class LC_SOLUTION_NAME(_2)
{
    static constexpr u32 max_items = 100'000;
    inline static constexpr auto primes = precompute_primes<max_items>();

public:
    inline static u32 counts[max_items + 1];
    inline static u64 storage[max_items];

    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 impl(const std::vector<std::vector<u32>>& items, u32 budget)
    {
        const auto n = static_cast<u32>(items.size());
        std::fill_n(counts, n + 1, 0u);

        u32 min_price = ~u32{};
        u32 min_price_factor = 0;
        u32 max_price = 0;

        for (auto& item : items)
        {
            const auto* row = item.data();
            u32 factor = row[0];
            u32 price = row[1];
            if (price < min_price)
            {
                min_price = price;
                min_price_factor = factor;
            }
            max_price = max2(max_price, price);
            ++counts[factor];
        }

        const u32 max_purchases = budget / min_price;
        if (!max_purchases) return 0;
        if (max_purchases < n)
        {
            if (min_price_factor == 1) return 2 * max_purchases;
            u32 cheapest_gain = counts[min_price_factor] - 1;
            for (u32 m = 2 * min_price_factor;
                 m <= n && cheapest_gain < max_purchases;
                 m += min_price_factor)
            {
                cheapest_gain += counts[m];
            }
            if (cheapest_gain >= max_purchases) return 2 * max_purchases;
        }

        for (const u32 p : primes.data)
        {
            assert(p >= 2);
            if (p > n) break;
            for (u32 i = n / p; i >= 1; --i)
            {
                u32 next = i * p;
                counts[i] += counts[next];
            }
        }

        const u32 max_offset =
            min2(min_price - 1, min2(budget, max_price) - min_price);
        if (max_offset < n)
        {
            auto* totals = storage;
            std::fill_n(totals, max_offset + 1, u64{});
            for (auto& item : items)
            {
                const auto* row = item.data();
                const u32 offset = row[1] - min_price;
                if (offset <= max_offset)
                {
                    totals[offset] += counts[row[0]] - 1;
                }
            }
            u32 answer = 0;
            for (u32 offset = 0;
                 offset <= max_offset && min_price + offset <= budget;
                 ++offset)
            {
                if (!totals[offset]) continue;
                const u32 price = min_price + offset;
                const u32 can_buy =
                    static_cast<u32>(min2(totals[offset], u64{budget / price}));
                answer += 2 * can_buy;
                budget -= price * can_buy;
            }
            return answer + budget / min_price;
        }

        auto* sorted = storage;
        u32 num_sorted = 0;
        u32 offset_bits = 0;
        for (auto& item : items)
        {
            const auto* row = item.data();
            u32 factor = row[0];
            u32 price = row[1];

            const u32 free_items = counts[factor] - 1;
            const u32 offset = price - min_price;
            const bool keep = free_items != 0 && offset <= max_offset;
            sorted[num_sorted] = (u64{offset} << 32) | free_items;
            num_sorted += keep;
            offset_bits |= keep ? offset : 0;
        }

        adaptive_sort<32, max_items, 32>(sorted, num_sorted, offset_bits);

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
