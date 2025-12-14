#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minPathSum(
        std::vector<std::vector<int>>& grid) noexcept
    {
        const auto h = grid.size(), w = grid[0].size();

        // Handle the first row
        for (size_t x = 1; x != w; ++x) grid[0][x] += grid[0][x - 1];

        // Handle the first column
        for (size_t y = 1; y != h; ++y) grid[y][0] += grid[y - 1][0];

        // The body
        for (size_t y = 1; y != h; ++y)
        {
            auto &curr = grid[y], &prev = grid[y - 1];
            for (size_t x = 1; x != w; ++x)
            {
                curr[x] += std::min(curr[x - 1], prev[x]);
            }
        }

        return grid[h - 1][w - 1];
    }
};
