#include <cstdint>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] constexpr std::vector<std::vector<int>> shiftGrid(
        std::vector<std::vector<int>>& grid,
        u16 k) noexcept
    {
        const u16 rows = grid.size() & 0xFFFF;
        const u16 columns = grid.front().size() & 0xFFFF;
        const u16 n = rows * columns;
        k %= n;
        if (!k) return grid;

        std::vector<std::vector<int>> r(rows, std::vector<int>(columns));
        const u16 jump = n - k;

        for (u16 y = 0; y != rows; ++y)
        {
            u16 offset = y * columns + jump;
            for (u16 x = 0; x != columns; ++x)
            {
                u16 src_index = (offset + x) % n;
                r[y][x] = grid[src_index / columns][src_index % columns];
            }
        }

        return r;
    }
};
