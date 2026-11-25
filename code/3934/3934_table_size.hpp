#pragma once

#include <algorithm>
#include <bit>
#include <vector>

#include "3934_hash_table_storage.hpp"
#include "bitsets/bitset_view/bitset_view.hpp"
#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "integral_aliases.hpp"
#include "lower_bound.hpp"
#include "mod/mod_int_mul.hpp"
#include "mod/mod_int_sub.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

class LC_SOLUTION_NAME(_table_size)
{
public:
    inline static u32 prefix_hash[100'001];
    inline static constexpr u32 kBase = 911'382'323;
    inline static ModInt kBasePowers[100'001];
    inline static const bool precomputed = []
    {
        kBasePowers[0] = ModInt{1};
        for (u32 i = 1; i != 100'001; ++i)
        {
            kBasePowers[i] = kBasePowers[i - 1] * ModInt{kBase};
        }
        return true;
    }();

    static u32 next_hash(u32 prev_hash, u32 value)
    {
        return static_cast<u32>((u64{prev_hash} * kBase + value) % kMOD);
    }

    [[nodiscard, gnu::always_inline]] static u32 query_hash(
        u32 begin,
        u32 end) noexcept
    {
        const ModInt prefix =
            ModInt{prefix_hash[begin]} * kBasePowers[end - begin];
        return (ModInt{prefix_hash[end]} - prefix).value;
    }

    inline static HashTableStorage storage;

    template <u32 capacity>
    [[nodiscard, gnu::always_inline]] static bool exists_unique(
        u32 n,
        u32 k) noexcept
    {
        HashTable<capacity> hash_to_count{storage};
        bsv_fill<false>(BitsetView<u64, capacity>{storage.bits});
        u32 singletons = 0;
        for (u32 end = k; end != n + 1; ++end)
        {
            const u32 hash = query_hash(end - k, end);
            const u32 count = hash_to_count.increment(hash);
            singletons += (count == 1);
            singletons -= (count == 2);
        }
        return singletons != 0;
    }

    template <u32 max_n>
    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 impl(const u32* a, const u32 n) noexcept
    {
        {
            constexpr u32 kWords = 100'000 / 32 + 1;
            using View = BitsetView<u32, kWords * 32>;
            View seen{prefix_hash}, repeated{prefix_hash + kWords};
            bsv_fill<false>(seen);
            bsv_fill<false>(repeated);
            for (u32 i = 0; i != n; ++i)
            {
                const u32 value = a[i];
                bsv_set<true>(bsv_get(seen, value) ? repeated : seen, value);
            }
            for (u32 i = 0; i != kWords; ++i)
            {
                if (seen.words[i] & ~repeated.words[i]) return 1;
            }
        }

        prefix_hash[0] = 0;
        for (u32 i = 0; i != n; ++i)
        {
            prefix_hash[i + 1] = next_hash(prefix_hash[i], a[i]);
        }

        return lower_bound(
            u32{2},
            n,
            [n] [[gnu::always_inline]] (u32 k) noexcept
            { return exists_unique<std::bit_ceil(2 * max_n)>(n, k); });
    }

    static u32 smallestUniqueSubarray(std::vector<int>& nums)
    {
        constexpr decltype(&impl<32>) fns[]{
            impl<1u << 5>,
            impl<1u << 6>,
            impl<1u << 7>,
            impl<1u << 8>,
            impl<1u << 9>,
            impl<1u << 10>,
            impl<1u << 11>,
            impl<1u << 12>,
            impl<1u << 13>,
            impl<1u << 14>,
            impl<1u << 15>,
            impl<1u << 16>,
            impl<100'000>,
        };
        const u32 n = nums.size() & ~u32{};
        const auto index = std::max(std::bit_width(n - 1), 5) - 5;
        return fns[index](reinterpret_cast<const u32*>(nums.data()), n);
    }
};
