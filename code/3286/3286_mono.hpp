#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>






template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    inline static constexpr u32 dx[4]{0u, -1u, 1u, 0u};
    inline static constexpr u32 dy[4]{-1u, 0u, 0u, 1u};

    [[nodiscard, gnu::always_inline]] static constexpr u16 pack(
        u32 x,
        u32 y) noexcept
    {
        return ((x << 8) | y) & 0xffff;
    }

    [[nodiscard, gnu::always_inline]] static constexpr std::pair<u32, u32>
    unpack(u16 p) noexcept
    {
        return {p >> 8, p & 0xff};
    }

    constexpr bool findSafeWalk(
        const std::vector<std::vector<int>>& grid,
        u32 health) const noexcept
    {
        u8 qs = 0;
        u16 c[64][64], q[256];
        const u32 h = static_cast<u32>(grid.size());
        const u32 w = static_cast<u32>(grid[0].size());
        const u16 target = pack(w - 1, h - 1);
        for (u8 y = 0; y != h; ++y)
        {
            for (u16 x = 0; x != w; ++x)
            {
                u32 v = grid[y][x] & 1;
                c[y][x] = pack(v << 1, health);
            }
        }

        bool result = false;
        auto enqueue =
            [&] [[gnu::always_inline]] (u32 x, u32 y, u32 cost) noexcept
        {
            auto [vq, min_cost] = unpack(c[y][x]);
            u32 t = (vq >> 1) + cost;
            bool b = (x == w) | (y == h) | (t >= min_cost);
            c[y][x] = iif(b, c[y][x], pack(vq | 1, t));
            q[qs] = pack(x, y);
            result |= (target == q[qs]) & !b;
            qs += !(vq & 1) & !b;
        };

        enqueue(0, 0, 0);

        while (!((!qs) | result))
        {
            auto [x, y] = unpack(q[--qs]);
            auto [vq, min_cost] = unpack(c[y][x]);
            c[y][x] = pack(vq & 0b10, min_cost);

            for (u32 i = 0; i != 4; ++i)
            {
                u32 nx = std::min(w, x + dx[i]);
                u32 ny = std::min(h, y + dy[i]);
                enqueue(nx, ny, min_cost);
            }
        }

        return result;
    }
};

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
