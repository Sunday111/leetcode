#include <algorithm>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr auto largestSquareArea(
        const std::vector<std::vector<int>>& bottomLeft,
        const std::vector<std::vector<int>>& topRight) noexcept
    {
        struct Rect
        {
            int x1, y1, x2, y2;
            constexpr auto operator<=>(const Rect&) const noexcept = default;
        };

        const u32 n = static_cast<u32>(bottomLeft.size());
        static Rect rects[1000];
        for (u32 i = 0; i != n; ++i)
        {
            auto& ri = rects[i];
            ri.x1 = bottomLeft[i][0];
            ri.y1 = bottomLeft[i][1];
            ri.x2 = topRight[i][0];
            ri.y2 = topRight[i][1];
        }

        std::ranges::sort(rects, rects + n);

        int ans = 0;
        for (u32 i = 0; i != n; ++i)
        {
            auto& ri = rects[i];
            for (u32 j = i + 1; j != n; ++j)
            {
                auto& rj = rects[j];

                if (rj.x1 > ri.x2) break;

                int a = std::min(ri.x2, rj.x2) - rj.x1;
                int b = std::min(ri.y2, rj.y2) - std::max(ri.y1, rj.y1);
                ans = std::max(ans, std::min(a, b));
            }
        }

        return 1L * ans * ans;
    }
};
