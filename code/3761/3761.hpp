#include <bit>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "upd_min.hpp"

struct Entry
{
    u32 key;
    u32 value;
};

inline static Entry gTableEntries[1 << 18];  // NOLINT
inline static u64 gTableBits[1 << 18];       // NOLINT

template <u32 capacity>
struct HashTable
{
    Entry* table;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);

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
    [[nodiscard, gnu::always_inline]] static constexpr u32 reverse(
        u32 x) noexcept
    {
        u32 r = 0;
        while (x)
        {
            r = r * 10 + x % 10;
            x /= 10;
        }
        return r;
    }

    template <u32 capacity>
    [[nodiscard]] static u32 impl(std::vector<u32>& nums) noexcept
    {
        HashTable<capacity> m;
        u32 n = cast<u32>(nums.size()), r = ~u32{};
        [[assume(n < capacity)]];
        for (u32 i = 0; i != n; ++i)
        {
            u32 v = nums[i];
            if (auto it = m.find(v))
            {
                upd_min(r, i - *it);
            }
            m.insert(reverse(v), i);
        }
        return r;
    }

    [[nodiscard]] int minMirrorPairDistance(
        std::vector<int>& nums) const noexcept
    {
        static_assert(std::bit_width(100'000u) == 17);

        constexpr std::array fns{
            impl<1 << 5>,
            impl<1 << 6>,
            impl<1 << 7>,
            impl<1 << 8>,
            impl<1 << 9>,
            impl<1 << 10>,
            impl<1 << 11>,
            impl<1 << 12>,
            impl<1 << 13>,
            impl<1 << 14>,
            impl<1 << 15>,
            impl<1 << 16>,
            impl<1 << 17>,
            impl<1 << 18>,
        };

        return std::bit_cast<int>(
            fns[cast<u8>(std::max(std::bit_width(nums.size()) + 1, 5)) - 5](
                reinterpret_cast<std::vector<u32>&>(nums)));
    }
};
