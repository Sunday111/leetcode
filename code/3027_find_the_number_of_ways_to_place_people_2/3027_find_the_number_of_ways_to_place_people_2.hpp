#pragma once

#include <algorithm>
#include <array>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define HOT_PATH __attribute__((hot))

class Solution
{
public:
    using Index = uint16_t;   // [0; 1000)
    using Coord = int32_t;    // [-10^9; 10^9]
    using Result = uint16_t;  // < 1000x1000 ?

    struct Point
    {
        Coord x, y;

        [[nodiscard]] FORCE_INLINE HOT_PATH constexpr bool operator<(
            const Point& r) const noexcept
        {
            return (x < r.x) || (x == r.x && y > r.y);
        }
    };

    [[nodiscard]] static constexpr Result numberOfPairs(
        const std::vector<std::vector<int>>& in) noexcept
    {
        std::array<Point, 1000> points;  // NOLINT
        Index n = 0;
        for (auto& p : in)
        {
            points[n++] = {
                .x = static_cast<Coord>(p[0]),
                .y = static_cast<Coord>(p[1]),
            };
        }

        std::ranges::sort(
            points.begin(),
            std::next(points.begin(), n),
            std::less{});

        Result r = 0;

        for (Index i = 0; i != n; ++i)
        {
            auto& a = points[i];
            Coord min_y = std::numeric_limits<Coord>::lowest();
            for (Index j = i + 1; j != n && min_y <= a.y; ++j)
            {
                if (auto& b = points[j]; b.y <= a.y && b.y >= min_y)
                {
                    ++r;
                    min_y = b.y + 1;
                }
            }
        }

        return r;
    }
};
