#include <bit>
#include <cassert>
#include <cstring>
#include <memory>
#include <vector>

#include "bitsets/ctl_zero.hpp"
#include "integral_aliases.hpp"
#include "math/precompute_primes.hpp"
#include "minmax/max2.hpp"
#include "minmax/min2.hpp"
#include "radix_sort/adaptive_sort.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

class LC_SOLUTION_NAME(_4)
{
    struct Item
    {
        u32 factor;
        u32 price;
    };

    static constexpr u32 max_items = 100'000;
    inline static constexpr auto primes = precompute_primes<max_items / 2>();
    inline static u32 counts[max_items + 1];
    inline static u64 entries[max_items];

    [[gnu::always_inline]] static void sort_small(u64* data, u32 size) noexcept
    {
        for (u32 i = 1; i < size; ++i)
        {
            const u64 entry = data[i];
            u32 j = i;
            while (j && entry < data[j - 1])
            {
                data[j] = data[j - 1];
                --j;
            }
            data[j] = entry;
        }
    }

    [[gnu::always_inline]] static void trim_by_purchase_limit(
        u32& num_sorted,
        u32& offset_bits,
        u32 max_purchases) noexcept
    {
        if (num_sorted < 512 || max_purchases >= num_sorted / 4) return;

        // Each entry can supply at least one pair. Keep the price bucket
        // containing the last affordable rank and every cheaper bucket.
        constexpr u32 bucket_bits = 8;
        constexpr u32 num_buckets = 1u << bucket_bits;
        u32 bucket_counts[num_buckets]{};
        const u32 width = 32 - ctl_zero(offset_bits | (num_buckets - 1));
        const u32 shift = width - bucket_bits;
        for (u32 i = 0; i != num_sorted; ++i)
        {
            const u32 offset = static_cast<u32>(entries[i] >> 32);
            ++bucket_counts[offset >> shift];
        }

        u32 bucket = 0;
        while (bucket_counts[bucket] < max_purchases)
        {
            max_purchases -= bucket_counts[bucket++];
        }
        offset_bits = ((bucket + 1) << shift) - 1;
        u32 kept = 0;
        for (u32 i = 0; i != num_sorted; ++i)
        {
            const u64 entry = entries[i];
            entries[kept] = entry;
            kept += static_cast<u32>(entry >> 32) <= offset_bits;
        }
        num_sorted = kept;
    }

    // Zero means the full algorithm must finish the calculation.
    [[gnu::always_inline]] static u32 try_price_prefix(
        u32 n,
        u32 max_factor,
        u32 min_price,
        u32 max_offset,
        u32 prefix_offset,
        u32 budget,
        u32 max_purchases) noexcept
    {
        constexpr u32 prefix_capacity = 256;
        auto* prefix = RadixSortStorage::scratch<u64, max_items>;
        u32 size = 0;
        u32 min_price_free_items = 0;
        for (u32 i = 0; i != n; ++i)
        {
            Item item{};
            std::memcpy(&item, &entries[i], sizeof(item));
            if (item.price - min_price > prefix_offset) continue;
            if (item.price == min_price)
            {
                min_price_free_items += counts[item.factor] - 1;
                if (min_price_free_items >= max_purchases)
                {
                    return 2 * max_purchases;
                }
            }
            if (size == prefix_capacity) return 0;
            prefix[size++] = (u64{item.price} << 32) | item.factor;
        }

        // Count multiples only for affordable entries, stopping once their
        // supply suffices.
        sort_small(prefix, size);
        u32 pairs = 0;
        u32 remaining_lookups = n;
        for (u32 i = 0; i != size; ++i)
        {
            const u32 price = static_cast<u32>(prefix[i] >> 32);
            if (price > budget) break;
            const auto factor = static_cast<u32>(prefix[i]);
            const u32 can_buy = budget / price;
            u32 free_items = n - 1;
            if (factor != 1)
            {
                free_items = counts[factor] - 1;
                for (u32 multiple = 2 * factor;
                     free_items < can_buy && multiple <= max_factor;
                     multiple += factor)
                {
                    if (!remaining_lookups) return 0;
                    --remaining_lookups;
                    free_items += counts[multiple];
                }
            }
            const u32 take = min2(can_buy, free_items);
            pairs += take;
            budget -= take * price;
        }

        // The next omitted price is at least min_price + prefix_offset + 1.
        if (prefix_offset < max_offset && budget > min_price + prefix_offset)
        {
            return 0;
        }
        return 2 * pairs + budget / min_price;
    }

public:
    [[gnu::target("popcnt,bmi,bmi2,lzcnt,avx2"),
      gnu::flatten,
      gnu::no_sanitize_address]]
    static u32 maximumSaleItems(
        const std::vector<std::vector<int>>& items,
        u32 budget) noexcept
    {
        const auto n = static_cast<u32>(items.size());
        std::memset(counts, 0, (n + 1) * sizeof(u32));

        // Flatten the rows and count factors. Equal minimum prices favour the
        // smaller factor.
        u64 cheapest_item = (u64{1'000'000'001} << 32) | 1u;
        u32 max_price = 0;
        u32 max_factor = 0;
        u32 written = 0;
        for (const auto& item : items)
        {
            u64 entry{};
            std::memcpy(&entry, std::to_address(item.begin()), sizeof(entry));
            entries[written++] = entry;
            const auto [factor, price] = std::bit_cast<Item>(entry);
            cheapest_item = min2(cheapest_item, (u64{price} << 32) | factor);
            max_price = max2(max_price, price);
            max_factor = max2(max_factor, factor);
            ++counts[factor];
        }

        const auto min_price = static_cast<u32>(cheapest_item >> 32);
        const auto min_price_factor = static_cast<u32>(cheapest_item);
        const u32 max_purchases = budget / min_price;
        if (!max_purchases) return 0;

        // A single cheapest item can sometimes supply every affordable pair.
        if (max_purchases < n)
        {
            if (min_price_factor == 1) return 2 * max_purchases;
            u32 free_items = counts[min_price_factor] - 1;
            for (u32 multiple = 2 * min_price_factor;
                 multiple <= max_factor && free_items < max_purchases;
                 multiple += min_price_factor)
            {
                free_items += counts[multiple];
            }
            if (free_items >= max_purchases) return 2 * max_purchases;
        }

        const u32 max_offset =
            min2(min_price - 1, min2(budget, max_price) - min_price);
        // For a small budget and a wide price range, try the cheapest price
        // band first.
        const u32 span = max_price - min_price;
        if (n >= 256 && max_purchases <= 64 && max_offset >= n)
        {
            const u32 prefix_offset =
                min2(max_offset, static_cast<u32>((u64{span} * 16) / n));
            if (const u32 answer = try_price_prefix(
                    n,
                    max_factor,
                    min_price,
                    max_offset,
                    prefix_offset,
                    budget,
                    max_purchases))
            {
                return answer;
            }
        }

        // Sum multiples directly for small factors, or use the prime sieve for
        // a larger range.
        if (max_factor <= 32)
        {
            for (u32 factor = 2; factor <= max_factor / 2; ++factor)
            {
                if (!counts[factor]) continue;
                for (u32 multiple = 2 * factor; multiple <= max_factor;
                     multiple += factor)
                {
                    counts[factor] += counts[multiple];
                }
            }
        }
        else
        {
            for (const u32 prime : primes.data)
            {
                assert(prime >= 2);
                if (prime > max_factor / 2) break;
                for (u32 factor = max_factor / prime; factor >= 2; --factor)
                {
                    counts[factor] += counts[factor * prime];
                }
            }
        }
        counts[1] = n;

        // Group offers by exact price when the useful offsets fit in the
        // scratch array.
        if (max_offset < n)
        {
            auto* totals = RadixSortStorage::scratch<u64, max_items>;
            std::memset(totals, 0, (max_offset + 1) * sizeof(u64));
            for (u32 i = 0; i != n; ++i)
            {
                const auto [factor, price] = std::bit_cast<Item>(entries[i]);
                const u32 offset = price - min_price;
                if (offset <= max_offset)
                {
                    totals[offset] += counts[factor] - 1;
                    if (!offset && totals[0] >= max_purchases)
                    {
                        return 2 * max_purchases;
                    }
                }
            }
            u32 answer = 0;
            for (u32 offset = 0;
                 offset <= max_offset && min_price + offset <= budget;
                 ++offset)
            {
                if (!totals[offset]) continue;
                const u32 price = min_price + offset;
                const auto can_buy =
                    static_cast<u32>(min2(totals[offset], u64{budget / price}));
                answer += 2 * can_buy;
                budget -= price * can_buy;
            }
            return answer + budget / min_price;
        }

        // For wider ranges, take the cheapest pairs and compact other useful
        // offers in place.
        u32 min_price_free_items = 0;
        u32 num_sorted = 0;
        u32 offset_bits = 0;
        for (u32 i = 0; i != n; ++i)
        {
            const auto [factor, price] = std::bit_cast<Item>(entries[i]);
            const u32 free_items = counts[factor] - 1;
            const u32 offset = price - min_price;
            if (!offset)
            {
                min_price_free_items += free_items;
                if (min_price_free_items >= max_purchases)
                {
                    return 2 * max_purchases;
                }
                continue;
            }
            const bool keep = free_items != 0 && offset <= max_offset;
            entries[num_sorted] = (u64{offset} << 32) | free_items;
            num_sorted += keep;
            offset_bits |= keep ? offset : 0;
        }

        budget -= min_price_free_items * min_price;
        // Trim the expensive tail, then buy pairs in ascending price order.
        trim_by_purchase_limit(
            num_sorted,
            offset_bits,
            max_purchases - min_price_free_items);
        if (num_sorted < 64)
        {
            sort_small(entries, num_sorted);
        }
        else
        {
            adaptive_sort<32, max_items, 32>(entries, num_sorted, offset_bits);
        }

        u32 answer = 2 * min_price_free_items;
        for (u32 i = 0; i != num_sorted; ++i)
        {
            const u32 price = static_cast<u32>(entries[i] >> 32) + min_price;
            const auto free_items = static_cast<u32>(entries[i]);
            const u32 can_buy = min2(budget / price, free_items);
            if (!can_buy) break;
            answer += 2 * can_buy;
            budget -= price * can_buy;
        }
        return answer + budget / min_price;
    }
};
