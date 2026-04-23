#include <algorithm>
#include <bit>
#include <vector>

#include "cast.hpp"
#include "ceil_div.hpp"
#include "integral_aliases.hpp"

template <typename Value>
struct Entry
{
    u32 key;
    Value value;
};

inline static u8 gTableEntries[1 << 23];              // NOLINT
inline static u64 gTableBits[ceil_div(1 << 18, 64)];  // NOLINT

template <u32 capacity, typename Value>
struct HashTable
{
    Entry<Value>* table;
    u64* bits;

    static_assert(
        std::popcount(capacity) == 1,
        "Capacity must be a power of 2");
    inline static constexpr u32 kMask = capacity - 1;
    inline static constexpr u32 kNumWords = std::max(1u, capacity / 64);

    [[gnu::always_inline]] HashTable()
    {
        table = reinterpret_cast<Entry<Value>*>(gTableEntries);
        bits = gTableBits;
        std::fill_n(bits, kNumWords, u64{});
    }

    [[nodiscard, gnu::always_inline]] static constexpr u32 hash(u32 x) noexcept
    {
        u64 z = x;
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    [[gnu::always_inline]] constexpr Value& find_or_add(
        u32 k,
        Value v = {}) noexcept
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
        if (!(bits[wi] & m)) e.value = v;
        bits[wi] |= m;
        return e.value;
    }
};

class Solution
{
public:
    struct Info
    {
        u64 s{};
        u32 n{};
    };

    template <u32 capacity>
    static void impl(const u32* nums, u64* r, const u32 n) noexcept
    {
        HashTable<capacity, Info> m;
        for (u64 i{}; i != n; ++i)
        {
            auto& x = m.find_or_add(nums[i]);
            r[i] += x.n * i - x.s;
            x.s += i;
            x.n += 1;
        }
        for (u64 i{}; i != n; ++i)
        {
            auto& x = m.find_or_add(nums[i]);
            x.s -= i;
            x.n -= 1;
            r[i] -= x.n * i - x.s;
        }
    }

    auto distance(const std::vector<int>& nums) const noexcept
    {
        const u32 n = cast<u32>(nums.size());
        std::vector<long long> r;
        r.resize(n);
        static_assert(sizeof(long long) == sizeof(u64));
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
        fns[cast<u8>(std::max(std::bit_width(n) + 1, 5)) - 5](
            reinterpret_cast<const u32*>(nums.data()),
            reinterpret_cast<u64*>(r.data()),
            n);
        return r;
    }
};
