#include <bit>
#include <numeric>
#include <vector>

#include "bump_allocator.hpp"
#include "integral_aliases.hpp"
#include "negate_if.hpp"

template <typename Key, u32 capacity, typename Storage>
struct HashTable
{
    struct Entry
    {
        Key key;
        u32 value;
    };

    Entry* table;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);

    FORCE_INLINE HashTable()
    {
        table = BumpAllocator<Entry, Storage>{}.allocate(capacity);
        bits = BumpAllocator<u64, Storage>{}.allocate(kNumWords);
        std::fill_n(bits, kNumWords, u64{0});
    }

    [[nodiscard]] FORCE_INLINE static constexpr u32 hash(u32 x) noexcept
    {
        u64 z = u64{x} + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[nodiscard]] FORCE_INLINE static constexpr u32 hash(u64 x) noexcept
    {
        u64 z = u64{x} + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    FORCE_INLINE constexpr u32* insert(Key k, u32 v) noexcept
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
        return &e.value;
    }

    FORCE_INLINE constexpr u32& get_or_add(Key k) noexcept
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
        e.value &= -u32{(bits[wi] & m) != 0};
        bits[wi] |= m;
        return e.value;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32* find(Key k) noexcept
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

using SolutionStorage = GlobalBufferStorage<1 << 25>;
class Solution
{
public:
    inline static constexpr int kBias = 1 << 11;

    FORCE_INLINE static u32 pack(int a, int b) noexcept
    {
        return std::bit_cast<u32>(i32{a + kBias} << 16) |
               std::bit_cast<u32>(b + kBias);
    }

    FORCE_INLINE static u64 pack(int a, int b, int c) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 50) |
               std::bit_cast<u64>(i64{b + kBias} << 30) |
               std::bit_cast<u64>(i64{c + kBias * kBias});
    }

    FORCE_INLINE static u64 pack(int a, int b, int c, int d) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 48) |
               std::bit_cast<u64>(i64{b + kBias} << 32) |
               std::bit_cast<u64>(i64{c + kBias} << 16) |
               std::bit_cast<u64>(i64{d + kBias});
    }

    [[nodiscard]] static u32 countTrapezoids(
        std::vector<std::vector<int>>& points) noexcept
    {
        const u16 n = points.size() & 0xFFFF;
        const u32 nn = u32{n} * (u32{n} - 1);

        if (nn < (1 << 10)) return countTrapezoidsT<1 << 10>(n, points);
        if (nn < (1 << 11)) return countTrapezoidsT<1 << 11>(n, points);
        if (nn < (1 << 12)) return countTrapezoidsT<1 << 12>(n, points);
        if (nn < (1 << 13)) return countTrapezoidsT<1 << 13>(n, points);
        if (nn < (1 << 14)) return countTrapezoidsT<1 << 14>(n, points);
        if (nn < (1 << 15)) return countTrapezoidsT<1 << 15>(n, points);
        if (nn < (1 << 16)) return countTrapezoidsT<1 << 16>(n, points);
        if (nn < (1 << 17)) return countTrapezoidsT<1 << 17>(n, points);
        return countTrapezoidsT<1 << 18>(n, points);
    }

    template <size_t cap>
    [[nodiscard]] static u32 countTrapezoidsT(
        u16 n,
        std::vector<std::vector<int>>& points) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        HashTable<u64, cap, SolutionStorage> coeff, midPointWslope, midPoint;
        HashTable<u32, cap, SolutionStorage> slope;

        u32 cnt = 0;
        for (u16 i = 0; i != n - 1; ++i)
        {
            const int x0 = points[i][0], y0 = points[i][1];
            for (u16 j = i + 1; j != n; ++j)
            {
                const int x1 = points[j][0], y1 = points[j][1];
                int a = y1 - y0, b = x0 - x1, c = y0 * x1 - y1 * x0;
                bool c1 = !a && b < 0;
                bool c2 = a < 0;
                bool c3 = !c1 && c2;
                bool c4 = c1 || c2;
                a = negate_if(c3, a);
                b = negate_if(c4, b);
                c = negate_if(c4, c);
                int gm = std::gcd(a, b), gc = std::gcd(gm, c);
                cnt += slope.get_or_add(pack(a / gm, b / gm))++;
                cnt -= coeff.get_or_add(pack(a / gc, b / gc, c / gc))++;
                cnt -= midPoint.get_or_add(pack(x0 + x1, y0 + y1))++;
                cnt += midPointWslope.get_or_add(
                    pack(x0 + x1, y0 + y1, a / gm, b / gm))++;
            }
        }
        return cnt;
    }
};
