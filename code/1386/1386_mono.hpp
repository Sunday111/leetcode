#include <algorithm>
#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    inline static u32 sorted[10'001];
    u32 maxNumberOfFamilies(
        const u32 last_y,
        const std::vector<std::vector<int>>& seats) noexcept
    {
        constexpr u32 x_width = 2;
        constexpr u32 x_mask = ((1u << x_width) - 1u);
        u32 n = 0, ans = 0, m = 0, py = 1;
        for (auto& seat : seats)
        {
            u32 y = static_cast<u32>(seat[0]);
            u32 x = seat[1] & 15;
            bool good = (x > 1) & (x < 10);
            u32 yx = (y << x_width) | ((x - 2) >> 1);
            sorted[n] = yx;
            n += good;
        }

        sorted[n++] = ((last_y + 1u) << x_width);

        std::sort(sorted, sorted + n);

        for (u32 i = 0; i != n; ++i)
        {
            const u32 yx = sorted[i];
            const u32 y = yx >> x_width, x = yx & x_mask;

            if (y != py)
            {
                u32 b1 = !(m & 0b0011) + !(m & 0b1100);
                bool b2 = !(b1 | (m & 0b0110));

                ans += b1;
                ans += b2;
                ans += 2u * (y - (py + 1));

                py = y;
                m = 0;
            }

            m |= 1u << x;
        }

        return ans;
    }
};
