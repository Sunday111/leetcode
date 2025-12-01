#include <bit>
#include <integral_aliases.hpp>
#include <vector>

#include "bump_vector.hpp"
#include "cast.hpp"
#include "reinterpret_range.hpp"

template <u32 capacity, typename Storage>
struct HashTable
{
    struct Entry
    {
        u32 key;
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
        u64 z = x;
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    FORCE_INLINE constexpr void insert(u32 k, u32 v) noexcept
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

    [[nodiscard]] FORCE_INLINE constexpr u32* find(u32 k) noexcept
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
private:
    using SolutionStorage = GlobalBufferStorage<1 << 22>;
    static constexpr size_t kArrayCapacity = 100'000;

    template <u32 cap>
    [[nodiscard]] static int
    solve_map(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        HashTable<cap, SolutionStorage> m;
        m.insert(0, ~0u);
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            if (auto pj = m.find(x))
            {
                r = std::min(i - *pj, r);
            }
            m.insert(s, i);
        }
        return r == n ? -1 : cast<int>(r);
    }

    [[nodiscard]] static int
    solve_arr(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        BumpVector<u32, SolutionStorage> m;
        m.resize(p, 2 * n);

        m[0] = ~0u;
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            r = std::min(i - m[x], r);
            m[s] = i;
        }
        return r == n ? -1 : cast<int>(r);
    }

public:
    [[nodiscard]] static int minSubarray(
        std::vector<int>& nums_,
        u32 p) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        const auto nums = reinterpret_range<u32>(nums_);
        u32 target = 0, n = cast<u32>(nums.size());
        for (u32& v : nums) v = ((target += v) %= p);
        if (target == 0) return 0;  // No action needed
        if (p > n)
        {
            u32 t = 2 * n;
            if (t <= (1 << 9)) return solve_map<1 << 9>(nums, p, n, target);
            if (t <= (1 << 10)) return solve_map<1 << 10>(nums, p, n, target);
            if (t <= (1 << 11)) return solve_map<1 << 11>(nums, p, n, target);
            if (t <= (1 << 12)) return solve_map<1 << 12>(nums, p, n, target);
            if (t <= (1 << 13)) return solve_map<1 << 13>(nums, p, n, target);
            if (t <= (1 << 14)) return solve_map<1 << 14>(nums, p, n, target);
            if (t <= (1 << 15)) return solve_map<1 << 15>(nums, p, n, target);
            if (t <= (1 << 16)) return solve_map<1 << 16>(nums, p, n, target);
            if (t <= (1 << 13)) return solve_map<1 << 13>(nums, p, n, target);
            if (t <= (1 << 17)) return solve_map<1 << 17>(nums, p, n, target);
            return solve_map<1 << 18>(nums, p, n, target);
        }
        else
        {
            return solve_arr(nums, p, n, target);
        }
    }
};
