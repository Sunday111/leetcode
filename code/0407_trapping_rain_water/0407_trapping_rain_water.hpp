#include <algorithm>
#include <array>
#include <vector>

#include "cast.hpp"
#include "force_inline.hpp"
#include "hot_path.hpp"
#include "integral_aliases.hpp"
#include "no_sanitizers.hpp"

struct Vec2
{
    u8 x, y;
};

struct Entry
{
    Vec2 p;
    u16 h;
};

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

struct ArrayBucket
{
    [[nodiscard]] FORCE_INLINE u16 size() const noexcept HOT_PATH NO_SANITIZERS
    {
        return cast<u16>(data.size());
    }
    FORCE_INLINE constexpr void clear() noexcept HOT_PATH NO_SANITIZERS
    {
        data.clear();
    }
    FORCE_INLINE void push(Vec2 v) noexcept HOT_PATH NO_SANITIZERS
    {
        data.push_back(v);
    }

    [[nodiscard]] FORCE_INLINE Vec2 pop() noexcept HOT_PATH NO_SANITIZERS
    {
        auto last = data.back();
        data.pop_back();
        return last;
    }

    std::vector<Vec2> data;
};

struct VectorBucket  // NOLINT
{
    [[nodiscard]] FORCE_INLINE u16 size() const noexcept { return sz; }
    FORCE_INLINE constexpr void clear() noexcept { sz = 0; }
    FORCE_INLINE void push(Vec2 v) noexcept HOT_PATH NO_SANITIZERS
    {
        data[sz++] = v;
    }

    [[nodiscard]] FORCE_INLINE Vec2 pop() noexcept HOT_PATH NO_SANITIZERS
    {
        return data[--sz];
    }

    std::array<Vec2, 20'001> data;
    u16 sz = 0;
};

using Bucket = VectorBucket;
constexpr bool kBranchlessClearBit = true;

struct BucketPriorityQueue
{
    static constexpr u16 kMaxVal = 20'001;
    static constexpr u16 kLayer1Size = (kMaxVal / 64) + 1;      // 313
    static constexpr u16 kLayer2Size = (kLayer1Size / 64) + 1;  // 5
    static constexpr u16 kLayer3Size = 1;

    std::array<Bucket, kMaxVal> buckets;

    std::array<u64, kLayer1Size> layer1{};
    std::array<u64, kLayer2Size> layer2{};
    u32 layer3 = 0;

    FORCE_INLINE void clear() noexcept HOT_PATH NO_SANITIZERS
    {
        for (auto& b : buckets) b.clear();
        std::ranges::fill(layer1, 0);
        std::ranges::fill(layer2, 0);
        layer3 = 0;
    }

    FORCE_INLINE void setBit(u16 h) noexcept HOT_PATH NO_SANITIZERS
    {
        u16 i1 = h / 64;
        u16 i2 = i1 / 64;
        layer1[i1] |= 1ull << (h % 64);
        layer2[i2] |= 1ull << (i1 % 64);
        layer3 |= 1u << i2;
    }

    // Branchless version
    FORCE_INLINE void clearBit(u16 h) noexcept HOT_PATH NO_SANITIZERS
    {
        if constexpr (kBranchlessClearBit)
        {
            u16 i1 = h / 64;
            u16 i2 = i1 / 64;
            u64 bit1 = 1ull << (h % 64);
            u64 bit2 = 1ull << (i1 % 64);
            u32 bit3 = 1u << i2;

            // mask = all 1s if bucket[h] is now empty, else 0
            u64 mask = -u64{buckets[h].size() == 0};

            // Apply masks branchlessly
            layer1[i1] &= ~(bit1 & mask);

            // mask for layer1[i1] being zero
            u64 mask1 = -u64{layer1[i1] == 0};
            layer2[i2] &= ~(bit2 & mask & mask1);

            // mask for layer2[i2] being zero
            u32 mask2 = -u32{layer2[i2] == 0};
            layer3 &= ~(bit3 & mask & mask2);
        }
        else
        {
            u16 i1 = h / 64, i2 = i1 / 64;
            if (buckets[h].size() == 0)
            {
                layer1[i1] &= ~(1ull << (h % 64));
                if (!layer1[i1])
                {
                    layer2[i2] &= ~(1ull << (i1 % 64));
                    if (!layer2[i2]) layer3 &= ~(1u << i2);
                }
            }
        }
    }

    FORCE_INLINE void emplace(Vec2 p, u16 h) noexcept
    {
        buckets[h].push(p);
        setBit(h);
    }

    [[nodiscard]] FORCE_INLINE Entry pop() noexcept HOT_PATH NO_SANITIZERS
    {
        // branchless min extraction
        u16 idx2 = cast<u16>(std::countr_zero(layer3));
        u64 w2 = layer2[idx2];
        u16 idx1 = cast<u16>(std::countr_zero(w2));
        u64 w1 = layer1[idx2 * 64 + idx1];
        u16 idx0 = cast<u16>(std::countr_zero(w1));
        u16 h = idx2 * 4096 + idx1 * 64 + idx0;
        Vec2 v = buckets[h].pop();
        clearBit(h);

        return Entry{v, h};
    }

    [[nodiscard]] FORCE_INLINE operator bool() const noexcept  // NOLINT
    {
        return layer3 != 0;
    }
};

class Solution
{
public:
    inline static BucketPriorityQueue q;  // NOLINT

    [[nodiscard]] FORCE_INLINE constexpr static u16 toIdx(
        const Vec2& v) noexcept
    {
        return cast<u16>((u16{v.x} << 8) | v.y);
    }

    [[nodiscard]] FORCE_INLINE constexpr static u16 getH(
        std::vector<std::vector<int>>& hmap,
        const Vec2& v) noexcept NO_SANITIZERS
    {
        return cast<u16>(hmap[v.y][v.x]);
    }

    [[nodiscard]] static constexpr u32 trapRainWater(
        std::vector<std::vector<int>>& hmap) noexcept HOT_PATH NO_SANITIZERS
    {
        const Vec2 size{
            cast<u8>(hmap[0].size()),
            cast<u8>(hmap.size()),
        };

        if (size.x < 3 || size.y < 3) return 0;

        static std::array<u8, 0xFFFF> visited;  // NOLINT
        std::ranges::fill_n(visited.begin(), toIdx(size), 0);

        const Vec2 lim{cast<u8>(size.x - 1), cast<u8>(size.y - 1)};

        q.clear();

        // Init heap with borders
        {
            for (u8 x = 0; x != size.x; ++x)
            {
                Vec2 p{.x = x, .y = 0};
                q.emplace(p, getH(hmap, p));
                visited[toIdx(p)] = 1;
                p.y = lim.y;
                q.emplace(p, getH(hmap, p));
                visited[toIdx(p)] = 1;
            }

            for (u8 y = 1; y != lim.y; ++y)
            {
                Vec2 p{.x = 0, .y = y};
                q.emplace(p, getH(hmap, p));
                visited[toIdx(p)] = 1;
                p.x = lim.x;
                q.emplace(p, getH(hmap, p));
                visited[toIdx(p)] = 1;
            }
        }

        u32 r = 0;
        while (q)
        {
            Vec2 left, right, bottom, top;  // NOLINT
            auto [p, h] = q.pop();

            auto test = [&](const Vec2& n)
            {
                if (n.x >= size.x || n.y >= size.y) return;
                u16 ni = toIdx(n);
                if (visited[ni]) return;
                visited[ni] = true;

                u16 hn = getH(hmap, n);
                q.emplace(n, h > hn ? h : hn);
                r += h > hn ? h - hn : 0;
            };

            left = p, --left.x, test(left);
            right = p, ++right.x, test(right);
            bottom = p, --bottom.y, test(bottom);
            top = p, ++top.y, test(top);
        }

        return r;
    }
};
