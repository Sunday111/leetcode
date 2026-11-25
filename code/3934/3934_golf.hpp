#pragma once

#include <bit>
#include <vector>

#include "bitsets/bitset_view/bitset_view.hpp"
#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "bitsets/ctl_zero.hpp"
#include "integral_aliases.hpp"
#include "lower_bound.hpp"
#include "mod/mod_int_mul.hpp"
#include "mod/mod_int_sub.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"  // IWYU pragma: keep

struct GolfHashTable
{
    inline static u32 table[std::bit_ceil(2u * 100'000)];
    u32 capacity;

    [[gnu::always_inline]] explicit GolfHashTable(u32 windows) noexcept
        : capacity(1u << (32 - ctl_zero(2 * windows - 1)))
    {
        for (u32 i = 0; i != capacity; ++i) table[i] = 0;
    }

    struct InsertResult
    {
        bool first;
        bool second;
    };

    // Zero marks an empty slot. The high bit marks a repeated hash.
    [[nodiscard, gnu::always_inline]] InsertResult counting_insert(
        u32 hash) noexcept
    {
        u32 i = static_cast<u32>((u64{hash} * 0x9e3779b97f4a7c15ULL) >> 32);
        const u32 key = hash + 1;
        constexpr u32 repeated = 1u << 31;
        u32 entry = 0;
        do
        {
            i = (i + 1) & (capacity - 1);
            entry = table[i];
        } while (entry && (entry & ~repeated) != key);
        table[i] = key | (entry != 0 ? repeated : 0);
        return {entry == 0, entry == key};
    }
};

class LC_SOLUTION_NAME(_golf)
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

    [[nodiscard, gnu::always_inline]] static bool exists_unique(
        u32 n,
        u32 k) noexcept
    {
        GolfHashTable hash_to_count{n - k + 1};
        u32 singletons = 0;
        for (u32 end = k; end != n + 1; ++end)
        {
            const auto [first, second] =
                hash_to_count.counting_insert(query_hash(end - k, end));
            singletons += first;
            singletons -= second;
        }
        return singletons != 0;
    }

    [[nodiscard]] static bool has_unique_value(const u32* a, u32 n) noexcept
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
            if (seen.words[i] & ~repeated.words[i]) return true;
        }
        return false;
    }

    [[nodiscard]] static bool is_middle_pair_unique(
        const u32* a,
        u32 n) noexcept
    {
        const u32 mid = n / 2;
        const u32 x = a[mid - 1], y = a[mid];
        for (u32 i = 1; i != n; ++i)
        {
            if (i != mid && a[i - 1] == x && a[i] == y) return false;
        }
        return true;
    }

    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 impl(const u32* a, const u32 n) noexcept
    {
        if (has_unique_value(a, n)) return 1;
        if (is_middle_pair_unique(a, n)) return 2;

        prefix_hash[0] = 0;
        for (u32 i = 0; i != n; ++i)
        {
            prefix_hash[i + 1] = next_hash(prefix_hash[i], a[i]);
        }

        return lower_bound(
            u32{2},
            n,
            [n] [[gnu::always_inline]] (u32 k) noexcept
            { return exists_unique(n, k); });
    }

    static u32 smallestUniqueSubarray(std::vector<int>& nums)
    {
        const u32 n = nums.size() & ~u32{};
        const auto* a = reinterpret_cast<const u32*>(nums.data());
        return impl(a, n);
    }
};
