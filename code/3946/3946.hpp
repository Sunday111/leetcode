#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "minmax/max2.hpp"
#include "minmax/min2.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

class LC_SOLUTION_NAME()
{
    struct Item
    {
        u16 factor;
        u16 price;
    };

    struct Offer
    {
        u32 price;
        u32 profit;
    };

    [[gnu::always_inline, gnu::flatten]] static void
    partition_by_density(Offer* offers, u32 count, u32 budget)
    {
        u32 first = 0;
        u32 last = count;
        u32 available = budget;
        u32 work_left = 8 * count;
        while (last - first > 1)
        {
            if (last - first > work_left)
            {
                std::sort(
                    offers + first,
                    offers + last,
                    [](Offer a, Offer b)
                    { return a.profit * b.price > b.profit * a.price; });
                return;
            }
            work_left -= last - first;
            const Offer reference = offers[first + (last - first) / 2];
            u32 better = first;
            u32 worse = last;
            u32 higher_cost = 0;
            u32 equal_cost = 0;
            for (u32 i = first; i < worse;)
            {
                const Offer offer = offers[i];
                const u32 offer_value = offer.profit * reference.price;
                const u32 reference_value = reference.profit * offer.price;
                if (offer_value > reference_value)
                {
                    higher_cost += offer.price;
                    std::swap(offers[better++], offers[i++]);
                }
                else if (offer_value < reference_value)
                {
                    std::swap(offers[i], offers[--worse]);
                }
                else
                {
                    equal_cost += offer.price;
                    ++i;
                }
            }
            if (available < higher_cost)
            {
                last = better;
            }
            else if (available >= higher_cost + equal_cost)
            {
                available -= higher_cost + equal_cost;
                first = worse;
            }
            else
            {
                break;
            }
        }
    }

    [[gnu::always_inline, gnu::flatten]] static u32
    best_offer_selection(Offer* offers, u32 count, u32 budget, u32 min_price)
    {
        partition_by_density(offers, count, budget);
        u32 pivot = 0;
        u32 left = budget;
        u32 greedy_profit = 0;
        while (offers[pivot].price <= left)
        {
            left -= offers[pivot].price;
            greedy_profit += offers[pivot++].profit;
        }
        const Offer split = offers[pivot];
        const u32 scaled_upper =
            greedy_profit * split.price + left * split.profit;
        for (u32 i = pivot + 1; i != count; ++i)
        {
            if (offers[i].price <= left)
            {
                left -= offers[i].price;
                greedy_profit += offers[i].profit;
            }
        }
        const u32 greedy_answer = (budget + greedy_profit) / min_price;
        const u32 required_profit = (greedy_answer + 1) * min_price - budget;
        if (scaled_upper < required_profit * split.price) return greedy_answer;
        // Reversing a fractional-knapsack choice costs the difference of
        // the cross products below, in units scaled by the split price.
        const u32 slack = scaled_upper - required_profit * split.price;
        u32 forced_profit = 0;
        u32 capacity = budget;
        u32 kept = 0;
        for (u32 i = 0; i != count; ++i)
        {
            const auto [price, profit] = offers[i];
            const u32 weighted_profit = profit * split.price;
            const u32 weighted_price = price * split.profit;
            if (i < pivot && weighted_profit - weighted_price > slack)
            {
                forced_profit += profit;
                capacity -= price;
            }
            else if (i < pivot || weighted_price - weighted_profit <= slack)
            {
                offers[kept++] = offers[i];
            }
        }
        u32 dp[1501]{};
        for (u32 i = 0; i != kept; ++i)
        {
            const auto [price, profit] = offers[i];
            for (u32 money = capacity + 1; money-- > price;)
            {
                dp[money] = max2(dp[money], dp[money - price] + profit);
            }
        }
        return max2(
            greedy_answer,
            (budget + forced_profit + dp[capacity]) / min_price);
    }

    [[gnu::always_inline, gnu::flatten]] static u32 equal_factor_items(
        const Item* affordable,
        u32 affordable_count,
        u32 gain,
        u32 budget,
        u32 min_price,
        u32 max_price)
    {
        if (min_price == max_price)
        {
            const u32 copies = budget / min_price;
            return copies + min2(copies, gain) * (gain - 1);
        }
        u16 price_freq[1501]{};
        for (u32 i = 0; i != affordable_count; ++i)
        {
            ++price_freq[affordable[i].price];
        }
        u32 purchased = 0;
        const u32 limit = min2(budget, gain * min_price);
        for (u32 price = min_price; price <= limit && price <= budget; ++price)
        {
            if (!price_freq[price]) continue;
            const u32 take = min2(u32{price_freq[price]}, budget / price);
            purchased += take;
            budget -= take * price;
        }
        return purchased * gain + budget / min_price;
    }

public:
    [[gnu::no_sanitize_address, gnu::flatten]]
    static u32 impl(const std::vector<std::vector<u32>>& items, u32 budget)
    {
        const u32 item_count = static_cast<u32>(items.size());
        if (item_count == 1) return budget / items[0][1];

        Item affordable[1000];
        u32 affordable_count = 0;
        u16 frequencies[1501]{};
        u32 min_factor = 1500;
        u32 max_factor = 0;
        u32 min_price = 1501;
        u32 max_price = 0;
        for (const auto& item : items)
        {
            const u32 factor = item[0];
            const u32 price = item[1];
            affordable[affordable_count].factor = factor & 0xffff;
            affordable[affordable_count].price = price & 0xffff;
            affordable_count += price <= budget;
            ++frequencies[factor];
            min_factor = min2(min_factor, factor);
            max_factor = max2(max_factor, factor);
            min_price = min2(min_price, price);
            max_price = max2(max_price, price);
        }
        if (min_price > budget) return 0;

        if (min_factor == max_factor)
        {
            return equal_factor_items(
                affordable,
                affordable_count,
                item_count,
                budget,
                min_price,
                max_price);
        }

        const u16* gains = frequencies;
        u16 cached_gains[1501];
        // For sparse inputs, visit the affordable factors directly.
        if (max_factor / 2 > min_factor + 3 * affordable_count)
        {
            for (u32 i = 0; i != affordable_count; ++i)
            {
                cached_gains[affordable[i].factor] = 0;
            }
            cached_gains[1] = item_count & 0xffff;
            for (u32 i = 0; i != affordable_count; ++i)
            {
                const u32 f = affordable[i].factor;
                if (cached_gains[f]) continue;
                u32 gain = frequencies[f];
                for (u32 multiple = 2 * f; multiple <= max_factor;
                     multiple += f)
                {
                    gain += frequencies[multiple];
                }
                cached_gains[f] = gain & 0xffff;
            }
            gains = cached_gains;
        }
        else
        {
            if (min_factor == 1)
            {
                frequencies[1] = item_count & 0xffff;
                ++min_factor;
            }
            for (u32 f = min_factor; f <= max_factor / 2; ++f)
            {
                u32 count = frequencies[f];
                if (!count) continue;
                for (u32 multiple = f + f; multiple <= max_factor;
                     multiple += f)
                {
                    count += frequencies[multiple];
                }
                frequencies[f] = count & 0xffff;
            }
        }

        if (min_price == max_price)
        {
            const u32 purchases = budget / min_price;
            u32 remaining = purchases;
            u32 total = purchases;
            u16 gain_freq[1001]{};
            for (u32 i = 0; i != affordable_count; ++i)
            {
                ++gain_freq[gains[affordable[i].factor] - 1];
            }
            for (u32 gain = item_count; remaining && --gain;)
            {
                const u32 take = min2(remaining, u32{gain_freq[gain]});
                total += take * gain;
                remaining -= take;
            }
            return total;
        }

        Offer offers[1000];
        u32 count = 0;
        u32 total_price = 0;
        u32 total_profit = 0;
        for (u32 i = 0; i != affordable_count; ++i)
        {
            const u32 price = affordable[i].price;
            const u32 value = gains[affordable[i].factor] * min_price;
            // Buying once earns this much more than spending on cheapest
            // copies, with item counts scaled by min_price.
            const u32 profit = max2(value, price) - price;
            offers[count] = {price, profit};
            count += profit != 0;
            total_price += profit ? price : 0;
            total_profit += profit;
        }
        if (total_price <= budget) return (budget + total_profit) / min_price;

        return best_offer_selection(offers, count, budget, min_price);
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
