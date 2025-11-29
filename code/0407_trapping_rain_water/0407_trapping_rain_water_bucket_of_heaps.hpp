#include <algorithm>
#include <array>
#include <vector>

#include "cast.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

struct Vec2
{
    u8 x, y;
};

template <u16 capacity>
struct PriorityQueue  // NOLINT
{
    struct Entry
    {
        Vec2 p;
        u16 h;
    };

    std::array<Entry, capacity> data;  // NOLINT
    u16 size = 0;

    template <typename Op>
    FORCE_INLINE constexpr void heapOp(Op&& op) noexcept
    {
        std::forward<Op>(op)(
            std::begin(data),
            std::next(std::begin(data), size),
            std::greater{},
            &Entry::h);
    }

    template <typename... Args>
    FORCE_INLINE constexpr void emplace(Args&&... args) noexcept
    {
        data[size++] = {std::forward<Args>(args)...};
        heapOp(std::ranges::push_heap);
    }

    [[nodiscard]] FORCE_INLINE constexpr auto pop() noexcept
    {
        heapOp(std::ranges::pop_heap);
        return data[--size];
    }

    FORCE_INLINE constexpr void initialize() noexcept
    {
        heapOp(std::ranges::make_heap);
    }

    FORCE_INLINE constexpr void clear() { size = 0; }
};

struct BucketPriorityQueue
{
    static constexpr u16 kSegment = 64;
    static constexpr u16 kMaxVal = 20'001;
    static constexpr u16 kNumBuckets = (kMaxVal / kSegment) + 1;

    using Bucket = PriorityQueue<kMaxVal>;
    std::array<Bucket, kNumBuckets> buckets;
    u16 minh = kNumBuckets;

    FORCE_INLINE constexpr void clear() noexcept
    {
        std::ranges::for_each(buckets, &Bucket::clear);
        minh = kNumBuckets;
    }

    [[nodiscard]] FORCE_INLINE constexpr auto pop() noexcept
    {
        return buckets[minh].pop();
    }

    FORCE_INLINE constexpr void emplace(Vec2 p, u16 h) noexcept
    {
        u16 bucketIndex = h / kSegment;
        buckets[bucketIndex].emplace(p, h);
        minh = std::min(bucketIndex, minh);
    }

    [[nodiscard]] FORCE_INLINE operator bool() noexcept  // NOLINT
    {
        while (minh != kNumBuckets && buckets[minh].size == 0)
        {
            ++minh;
        }

        return minh != kNumBuckets;
    }
};

class Solution
{
public:
    template <typename To>
    [[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
    {
        return static_cast<To>(v);
    }

    [[nodiscard]] FORCE_INLINE constexpr static u16 toIdx(
        const Vec2& v) noexcept
    {
        return cast<u16>((u16{v.x} << 8) | v.y);
    }

    [[nodiscard]] FORCE_INLINE constexpr static u16 getH(
        std::vector<std::vector<int>>& hmap,
        const Vec2& v) noexcept
    {
        return cast<u16>(hmap[v.y][v.x]);
    }

    inline static BucketPriorityQueue q;

    [[nodiscard]] static constexpr u32 trapRainWater(
        std::vector<std::vector<int>>& hmap) noexcept
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
