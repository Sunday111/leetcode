#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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
            for (u8 x = n; x--; ++x)
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

            u8 swap_idx = n;
            for (u8 y2 = y + 1; y2 != n; ++y2)
            {
                if (a[y2] <= y)
                {
                    swap_idx = y2;
                    break;
                }
            }

            if (swap_idx == 0xFF) return -1;

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
