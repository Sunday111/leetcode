#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "bitsets/bitset_view/bitset_view.hpp"
#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "mod/mod_int_mul.hpp"
#include "mod/mod_int_sub.hpp"
#include "namespaces.hpp"
#include "solution_name.hpp"

class LC_SOLUTION_NAME(_hash_table)
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

    static u32 query_hash(u32 begin, u32 end)
    {
        const ModInt prefix =
            ModInt{prefix_hash[begin]} * kBasePowers[end - begin];
        return (ModInt{prefix_hash[end]} - prefix).value;
    }

    struct HashTable
    {
        static constexpr u32 kCapacity = 1u << 17;
        struct Entry
        {
            u32 key;
            u32 value;
        };
        Entry table[kCapacity];
        u64 bits[kCapacity / 64];

        [[nodiscard, gnu::always_inline]] u32 increment(u32 k) noexcept
        {
            u64 z = u64{k} + 0x9e3779b97f4a7c15ULL;
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
            u32 i = static_cast<u32>(z >> 32);
            BitsetView<u64, kCapacity> used{bits};
            bool present = false;
            do
            {
                i = (i + 1) & (kCapacity - 1);
                present = bsv_get(used, i);
            } while (present & (table[i].key != k));

            auto& e = table[i];
            e.key = k;
            e.value = iif(present, e.value + 1, 1u);
            bsv_set<true>(used, i);
            return e.value;
        }
    };

    static bool exists_unique(u32 n, u32 k)
    {
        static HashTable hash_to_count;
        bsv_fill<false>(
            BitsetView<u64, HashTable::kCapacity>{hash_to_count.bits});
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

        return *stdr::lower_bound(
            stdv::iota(u32{2}, n),
            true,
            std::less{},
            std::bind_front(exists_unique, n));
    }

    static u32 smallestUniqueSubarray(std::vector<int>& nums)
    {
        return impl(
            reinterpret_cast<const u32*>(nums.data()),
            nums.size() & ~u32{});
    }
};
