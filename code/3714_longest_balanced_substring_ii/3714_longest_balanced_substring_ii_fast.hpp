#include <algorithm>
#include <cmath>
#include <string>
#include <utility>

#include "bump_allocator.hpp"
#include "int_if.hpp"

using SolutionStorage = GlobalBufferStorage<1 << 23>;

template <u32 capacity, typename Storage>
struct HashTable
{
    struct Entry
    {
        u64 key;
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

    [[nodiscard]] FORCE_INLINE static constexpr u32 hash(u64 x) noexcept
    {
        u64 z = x;
        z += 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return z >> 32U;
    }

    FORCE_INLINE constexpr u32 try_emplace(u64 k, u32 v) noexcept
    {
        u32 i = hash(k), wi{};
        u64 m{};

        do
        {
            i = (i + u32{1}) & kMask;
            wi = i >> 6;
            m = u64{1} << (i & u32{63});
        } while ((bits[wi] & m) && table[i].key != k);

        auto& e = table[i];
        const bool empty = (bits[wi] & m) == u64{0};
        e.key = iif<u64>(empty, k, e.key);
        e.value = iif<u32>(empty, v, e.value);
        bits[wi] |= m;
        return e.value;
    }
};

class Solution
{
public:
    [[nodiscard]] static u32 longestBalanced(std::string& s) noexcept
    {
        u32 n = static_cast<u32>(s.size());
        u32 ans = 1;

        for (char& c : s) c -= 'a';

        for (u32 i = 0, cnt = 1; i != n; ++i, ++cnt)
        {
            bool b = i + 1 == n || s[i + 1] != s[i];
            ans = std::max(ans, cnt & -u32{b});
            cnt &= -u32{!b};
        }

        if (ans == n) return ans;

        for (char c = 0; c != 3; ++c)
        {
            static int arrs[2][100'001];
            char c2 = static_cast<char>(((c + 1) % 3));
            int d = 0;
            std::fill_n(arrs[0], n + 1, -1);
            std::fill_n(arrs[1], n + 1, -1);
            arrs[0][0] = 0;
            for (u32 i = 0, lb = 0; i != n;)
            {
                bool is_c = s[i] == c;
                bool is_c2 = s[i] == c2;
                bool is_c3 = !is_c and !is_c2;
                d += is_c - is_c2;
                d = d & -!is_c3;
                ++i;
                lb = iif(is_c3, i, lb);
                auto& x = arrs[d < 0][std::abs(d)];
                bool b = std::cmp_greater_equal(x, lb);
                ans = std::max(ans, i - iif(b, static_cast<u32>(x), i));
                x = iif(b, x, static_cast<int>(i));
            }
        }

        const auto arena = SolutionStorage::Instance().StartArena();
        HashTable<1 << 17, SolutionStorage> mp;
        mp.try_emplace(0, 0);
        for (u32 a = 0, b = 0, i = 0; i != n;)
        {
            bool c0 = s[i] == 0;
            bool c1 = s[i] == 1;
            bool c2 = s[i] == 2;
            a += c0 - c1;
            b += c1 - c2;
            ++i;
            u64 key = (u64{a} << 32) | b;
            ans = std::max(ans, i - mp.try_emplace(key, i));
        }

        return ans;
    }
};

#include "sync_stdio.hpp"
