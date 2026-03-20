#include <ranges>
#include <vector>

#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"
#include "upd_min.hpp"

// https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/

class Solution
{
public:
    [[nodiscard]] auto minAbsDiff(
        std::vector<std::vector<int>>& orig,
        const u8 k) const noexcept
    {
        // make all values unsigned
        for (auto& v : orig | std::views::join) v += 100'000;

        auto& grid = reinterpret_cast<std::vector<std::vector<u32>>&>(orig);

        const u8 h = cast<u8>(grid.size()), w = cast<u8>(grid[0].size());
        const u8 hh = h + 1 - k, ww = w + 1 - k;

        static PyramidBitset<200'001> bs{};

        for (u8 sy = 0; sy != hh; ++sy)
        {
            u8 y_end = sy + k;
            for (u8 sx = 0; sx != ww; ++sx)
            {
                u8 x_end = sx + k;

                // For each submatrix of size k

                u16 n = 0;
                for (u8 y = sy; y != y_end; ++y)
                {
                    for (u8 x = sx; x != x_end; ++x)
                    {
                        n += bs.add_ex(grid[y][x]);
                    }
                }

                // Find the minimum absolute difference
                // AND clear the bitset at the same time
                u32 prev = bs.min();
                u32& r = grid[sy][sx] = bs.max() - prev;
                bs.remove(prev);

                while (--n)
                {
                    u32 v = bs.min();
                    bs.remove(v);
                    u32 delta = v - prev;
                    upd_min(r, iif(delta, delta, r));
                    prev = v;
                }
            }

            grid[sy].resize(ww);
        }

        grid.resize(hh);
        return std::move(orig);
    }
};
