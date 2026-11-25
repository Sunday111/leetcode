#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include "bitsets/bitset_view/bitset_view.hpp"
#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "integral_aliases.hpp"
#include "mod/mod_int_mul.hpp"
#include "mod/mod_int_sub.hpp"
#include "namespaces.hpp"
#include "solution_name.hpp"

class LC_SOLUTION_NAME()
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

    // test if there is an unique subarray of length k
    static bool exists_unique(u32 n, u32 k)
    {
        std::unordered_map<u32, u32> hash_to_count;
        for (u32 end = k; end != n + 1; ++end)
        {
            u32 hash = query_hash(end - k, end);
            hash_to_count[hash] += 1;
        }

        for (auto& [hash, count] : hash_to_count)
        {
            if (count == 1)
            {
                return true;
            }
        }

        return false;
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
