#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] int minSwaps(std::vector<std::vector<int>>& grid) noexcept
    {
        u8 n = grid.size() & 0xFF;
        u16 ans = 0;

        u8* a = reinterpret_cast<u8*>(grid[0].data());

        for (u8 y = 0; y != n; ++y)
        {
            auto& row = grid[y];
            a[y] = 0;
            for (u8 x = n - 1; x; --x)
            {
                if (row[x] != 0)
                {
                    a[y] = x;
                    break;
                }
            }
        }

        for (u8 y = 0; y < n - 1; ++y)
        {
            if (a[y] <= y) continue;

            u8 swap_idx = y;
            while (++swap_idx != n && a[swap_idx] > y);
            if (swap_idx == n) return -1;

            while (swap_idx != y)
            {
                std::swap(a[swap_idx], a[swap_idx - 1]);
                --swap_idx;
                ++ans;
            }
        }

        return ans;
    }
};
