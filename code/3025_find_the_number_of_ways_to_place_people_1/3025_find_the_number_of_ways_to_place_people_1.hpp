#pragma once

#include <algorithm>
#include <array>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define HOT_PATH __attribute__((hot))

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;

    struct Point
    {
        u8 x, y;

        [[nodiscard]] FORCE_INLINE HOT_PATH constexpr bool operator<(
            const Point& r) const noexcept
        {
            if (x == r.x) return y > r.y;
            return x < r.x;
        }
    };

    [[nodiscard]] static constexpr u16 numberOfPairs(
        const std::vector<std::vector<int>>& in) noexcept
    {
        std::array<Point, 50> points;  // NOLINT
        u8 n = 0;
        for (auto& p : in)
        {
            points[n++] = {
                .x = static_cast<u8>(p[0]),
                .y = static_cast<u8>(p[1]),
            };
        }

        std::ranges::sort(
            points.begin(),
            std::next(points.begin(), n),
            std::less{});

        u16 r = 0;

        for (u8 i = 0; i != n; ++i)
        {
            auto& a = points[i];
            u8 min_y = 0;
            for (u8 j = i + 1; j != n; ++j)
            {
                auto& b = points[j];
                if (b.y <= a.y)
                {
                    r += b.y >= min_y;
                    min_y = std::max<u8>(min_y, b.y + 1);
                    if (b.y == a.y) break;
                }
            }
        }

        return r;
    }
};
