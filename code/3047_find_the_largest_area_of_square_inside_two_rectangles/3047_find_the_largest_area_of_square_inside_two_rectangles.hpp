#include <algorithm>
#include <vector>

#include "force_inline.hpp"

struct Vec2
{
    int x, y;
};

struct Rect
{
    FORCE_INLINE constexpr int left_x() const noexcept { return bot_left.x; }
    FORCE_INLINE constexpr int right_x() const noexcept { return top_right.x; }
    Vec2 bot_left;
    Vec2 top_right;
};

// Intersection between two intervals described as [x1, x2] and [x3, x4]
template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr int
interval_intersection(T x1, T x2, T x3, T x4) noexcept
{
    return std::max(0, std::min(x2, x4) - std::max(x1, x3));
}

class Solution
{
public:
    auto largestSquareArea(
        const std::vector<std::vector<int>>& bottomLeft,
        const std::vector<std::vector<int>>& topRight)
    {
        size_t n = bottomLeft.size();

        static Rect rects[1000];
        for (size_t i = 0; i != n; ++i)
        {
            rects[i] = {
                .bot_left{.x = bottomLeft[i][0], .y = bottomLeft[i][1]},
                .top_right{.x = topRight[i][0], .y = topRight[i][1]},
            };
        }

        std::ranges::sort(rects, rects + n, std::less{}, &Rect::left_x);

        int ans = 0;
        for (size_t i = 0; i != n; ++i)
        {
            auto& ri = rects[i];
            for (size_t j = i + 1; j != n; ++j)
            {
                auto& rj = rects[j];

                if (rj.left_x() > ri.right_x()) break;

                int a = interval_intersection(
                    ri.bot_left.x,
                    ri.top_right.x,
                    rj.bot_left.x,
                    rj.top_right.x);
                int b = interval_intersection(
                    ri.bot_left.y,
                    ri.top_right.y,
                    rj.bot_left.y,
                    rj.top_right.y);
                ans = std::max(ans, std::min(a, b));
            }
        }

        return 1L * ans * ans;
    }
};
