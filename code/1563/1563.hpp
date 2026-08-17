#include <algorithm>
#include <numeric>
#include <vector>

#include "integral_aliases.hpp"

struct Entry
{
    u32 key;
    u32 value;
};

inline static Entry gTableEntries[1024];  // NOLINT
inline static u64 gTableBits[1024];       // NOLINT

template <u32 capacity = 1024>
struct HashTable
{
    Entry* table;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = capacity / 64;

    [[gnu::always_inline]] HashTable()
    {
        table = gTableEntries;
        bits = gTableBits;
        std::fill_n(bits, kNumWords, u64{0});
    }

    [[nodiscard, gnu::always_inline]] static constexpr u32 hash(u32 x) noexcept
    {
        u64 z = x;
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[gnu::always_inline]] constexpr void insert(u32 k, u32 v) noexcept
    {
        u32 i = hash(k);
        u32 wi;  // NOLINT
        u64 m;   // NOLINT

        do
        {
            i = ++i & kMask;
            wi = i >> 6;
            m = u64{1} << (i & 63);
        } while ((bits[wi] & m) && table[i].key != k);

        auto& e = table[i];
        e.key = k;
        e.value = v;
        bits[wi] |= m;
    }

    [[nodiscard, gnu::always_inline]] constexpr u32* find(u32 k) noexcept
    {
        u32 i = hash(k);
        bool b1, b2;  // NOLINT
        do
        {
            i = ++i & kMask;
            b1 = (bits[i >> 6] & (u64{1} << (i & 63)));
            b2 = table[i].key != k;
        } while (b1 && b2);

        u64 r = std::bit_cast<u64>(&table[i].value);
        r &= -u64{b1 && !b2};
        return std::bit_cast<u32*>(r);
    }
};

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] inline static constexpr u64 pack(
        u32 x,
        u32 y) noexcept
    {
        return (u64{x} << 32) | u64{y};
    }

    inline static u32 prefix[501];
    inline static u32 memo[500][501];
    u32 stoneGameV(std::vector<int>& stoneValue) noexcept
    {
        const u32 n = static_cast<u32>(stoneValue.size());
        [[assume(n != 0)]];
        const auto* const a = reinterpret_cast<const u32*>(stoneValue.data());
        std::exclusive_scan(a, a + n, prefix, u32{});
        prefix[n] = prefix[n - 1] + a[n - 1];

        for (u32 i = 0; i + 1 < n; ++i)
        {
            std::fill_n(memo[i] + i, n + 1 - i, ~u32{});
            memo[i][i + 1] = 0;
        }

        HashTable<> vals;
        for (u32 i = 1; i != n; ++i)
        {
            vals.insert(prefix[i], i);
        }

        return [&](this auto&& f, u32 begin, u32 end) -> u32
        {
            auto& r = memo[begin][end];

            if (r != ~u32{}) return r;

            r = 0;
            const u32 full_sum = (prefix[end] - prefix[begin]);

            // check special case where there are two equal subarrays
            if (!(full_sum & 1))
            {
                u32 half = full_sum / 2;
                if (auto mid = vals.find(prefix[begin] + half))
                {
                    return r = std::max(
                               half + f(begin, *mid),
                               half + f(*mid, end));
                }
            }

            for (u32 i = begin + 1; i != end; ++i)
            {
                u32 left = prefix[i] - prefix[begin];
                u32 right = full_sum - left;

                if (left > right)
                {
                    if (r >= 2 * right) break;
                    r = std::max(r, right + f(i, end));
                }
                else if (r < 2 * left)
                {
                    r = std::max(r, left + f(begin, i));
                }
            }

            return r;
        }(0, n);
    }
};
