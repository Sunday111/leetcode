#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    static constexpr unsigned kMod = 1'000'000'007;
    template <bool transpose = false>
    static u32 numberOfPaths(
        const std::vector<std::vector<int>>& grid,
        u8 k) noexcept
    {
        u16 h = grid.size() & 0xFFFF, w = grid[0].size() & 0xFFFF;
        if constexpr (transpose)
        {
            std::swap(w, h);
        }
        else if (w > h)
        {
            return numberOfPaths<true>(grid, k);
        }

        static unsigned top[50];
        static unsigned row[25'001 * 50];
        std::fill_n(row, ((w + 1) * k), 0);
        row[k] = 1;

        for (u16 py = 0, y = 1; y <= h; ++py, ++y)
        {
            auto *left = &row[0], *curr = left + k;
            for (u16 px = 0, x = 1; x <= w; ++x, ++px, left += k, curr += k)
            {
                u8 v = transpose ? grid[px][py] : grid[py][px];
                v %= k;
                std::copy_n(curr, k, top);
                for (u8 pm = 0; pm != k; ++pm)
                {
                    auto m = pm + v;
                    m -= (k & -(m >= k));
                    auto& c = curr[m];
                    c = left[pm] + top[pm];
                    c -= (kMod & std::bit_cast<u32>(-(c >= kMod)));
                }
            }
        }

        return row[w * k];
    }
};
