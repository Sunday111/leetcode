#include <utility>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr u8 kLeft = 0b0001;
    inline static constexpr u8 kRight = 0b0010;
    inline static constexpr u8 kUp = 0b0100;
    inline static constexpr u8 kDown = 0b1000;

    [[nodiscard, gnu::always_inline]] static constexpr u8 to_mask(
        int v) noexcept
    {
        u8 l = v == 1 || v == 3 || v == 5;
        u8 r = v == 1 || v == 4 || v == 6;
        u8 u = v == 2 || v == 5 || v == 6;
        u8 d = v == 2 || v == 3 || v == 4;
        return (l | (r << 1) | (u << 2) | (d << 3)) & 0xF;
    }

    [[nodiscard, gnu::always_inline]] static constexpr u8 inv(u8 m) noexcept
    {
        u8 r = m == kLeft;
        u8 l = m == kRight;
        u8 d = m == kUp;
        u8 u = m == kDown;
        return (l | (r << 1) | (u << 2) | (d << 3)) & 0xF;
    }

    [[nodiscard, gnu::always_inline]] static constexpr std::pair<u16, u16>
    to_offsets(u8 m) noexcept
    {
        u16 dx = u16{(kLeft & m) != 0} - u16{(kRight & m) != 0};
        u16 dy = u16{(kUp & m) != 0} - u16{(kDown & m) != 0};
        return {dx, dy};
    }

    u16 h, w;

    [[nodiscard, gnu::always_inline]]
    std::pair<bool, bool> solve(
        u8 prev_in,
        const std::vector<std::vector<int>>& g) const noexcept
    {
        if (!prev_in) return {false, false};
        u16 x = 0, y = 0;

        while (true)
        {
            auto [dx, dy] = to_offsets(prev_in);
            x += dx;
            y += dy;

            // check that position is valid
            if (x >= w || y >= h) return {false, false};

            // get the mask for the current cell
            u8 mask = to_mask(g[y][x]);

            if (!(prev_in & mask))
            {
                // No connection
                return {false, true};
            }

            // remove incoming direction and invert the mask
            prev_in = inv(mask & ~prev_in);

            // came back to the origin: loop
            if (x == 0 && y == 0) return {false, true};

            // reached target
            if (x == w - 1 && y == h - 1) return {true, false};
        }

        std::unreachable();
    }

    bool hasValidPath(std::vector<std::vector<int>>& g) noexcept
    {
        h = cast<u16>(g.size()), w = cast<u16>(g[0].size());
        if (h == 1 && w == 1) return true;
        auto corner = to_mask(g[0][0]);
        auto [found, cycle] = solve(inv(corner & kRight), g);
        if (!found && !cycle) found = solve(inv(corner & kDown), g).first;
        return found;
    }
};
