
#include <algorithm>
#include <array>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct Vec2
{
    u8 x, y;
};

struct PriorityQueue  // NOLINT
{
    struct Entry
    {
        Vec2 p;
        u16 h;
    };

    std::array<Entry, 200 * 200 + 1> data;  // NOLINT
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
        return to<u16>((u16{v.x} << 8) | v.y);
    }

    [[nodiscard]] FORCE_INLINE constexpr static u16 getH(
        std::vector<std::vector<int>>& hmap,
        const Vec2& v) noexcept
    {
        return to<u16>(hmap[v.y][v.x]);
    }

    inline static PriorityQueue q;

    [[nodiscard]] static constexpr u32 trapRainWater(
        std::vector<std::vector<int>>& hmap) noexcept
    {
        const Vec2 size{
            to<u8>(hmap[0].size()),
            to<u8>(hmap.size()),
        };

        if (size.x < 3 || size.y < 3) return 0;

        static std::array<u8, 0xFFFF> visited;  // NOLINT
        std::ranges::fill_n(visited.begin(), toIdx(size), 0);

        const Vec2 lim{to<u8>(size.x - 1), to<u8>(size.y - 1)};

        // Init heap with borders
        {
            for (u8 x = 0; x != size.x; ++x)
            {
                Vec2 p{.x = x, .y = 0};
                q.data[q.size++] = {p, getH(hmap, p)};
                visited[toIdx(p)] = 1;
                p.y = lim.y;
                q.data[q.size++] = {p, getH(hmap, p)};
                visited[toIdx(p)] = 1;
            }

            for (u8 y = 1; y != lim.y; ++y)
            {
                Vec2 p{.x = 0, .y = y};
                q.data[q.size++] = {p, getH(hmap, p)};
                visited[toIdx(p)] = 1;
                p.x = lim.x;
                q.data[q.size++] = {p, getH(hmap, p)};
                visited[toIdx(p)] = 1;
            }

            q.initialize();
        }

        u32 r = 0;
        while (q.size)
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
