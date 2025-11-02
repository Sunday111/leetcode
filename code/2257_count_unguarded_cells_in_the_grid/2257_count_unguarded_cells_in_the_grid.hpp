#include <algorithm>
#include <bit>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u32 = uint32_t;
using u64 = uint64_t;

struct BitsetView
{
    [[nodiscard]] FORCE_INLINE constexpr bool contains(u32 i) const noexcept
    {
        return words[i >> 6] & (u64{1} << (i & 63));
    }

    FORCE_INLINE constexpr void add(u32 i) noexcept
    {
        words[i >> 6] |= (u64{1} << (i & 63));
    }

    FORCE_INLINE constexpr void clear() noexcept
    {
        std::fill_n(words, num_words, 0);
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 count() const noexcept
    {
        u32 r = 0;
        for (u32 i = 0; i != num_words; ++i)
        {
            r += static_cast<u32>(std::popcount(words[i]));
        }
        return r;
    }

    u64* words{};
    u32 num_words = 0;
};

class Solution
{
public:
    static size_t countUnguarded(
        u32 h,
        u32 w,
        std::vector<std::vector<int>>& guards_,
        std::vector<std::vector<int>>& walls_)
    {
        const u32 t = w * h, nw = (t / 64) + 1;
        using U = std::vector<std::vector<u32>>;
        auto &guards = reinterpret_cast<U&>(guards_),
             walls = reinterpret_cast<U&>(walls_);
        static u64 buf[2 * ((100'001 / 64) + 1)];
        BitsetView visited{buf, nw}, obstacle{buf + nw, nw};
        visited.clear(), obstacle.clear();
        for (auto& g : guards) obstacle.add(g[0] * w + g[1]);
        for (auto& wall : walls) obstacle.add(wall[0] * w + wall[1]);
        auto visit = [&](u32 x, u32 y, u32 dx, u32 dy)
        {
            u32 i = w * y + x, o = dx ? dx : w * dy;
            x += dx, y += dy, i += o;
            while (x < w && y < h && !obstacle.contains(i))
            {
                visited.add(i);
                x += dx, y += dy, i += o;
            }
        };
        for (auto& g : guards)
        {
            u32 y = g[0], x = g[1];
            visit(x, y, 1, 0);
            visit(x, y, 0, 1);
            visit(x, y, ~0u, 0);
            visit(x, y, 0, ~0u);
        }

        return t - walls.size() - guards.size() - visited.count();
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
