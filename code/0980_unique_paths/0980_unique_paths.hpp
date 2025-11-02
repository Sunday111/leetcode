#include <array>
#include <span>
#include <vector>

class Solution
{
public:
    std::span<std::vector<int>> grid;
    using u32 = uint32_t;
    u32 w = 0, h = 0, r = 0, x = 0, y = 0;
    u32 e = 0;  // num empty
    u32 l = 0;  // current path length

    static constexpr std::array<std::pair<u32, u32>, 4> kOffsets{
        {{1, 0}, {-2, 0}, {1, 1}, {0, -2}}};

    static constexpr std::pair<u32, u32> kReset = []()
    {
        u32 x = 0, y = 0;
        for (auto [dx, dy] : kOffsets)
        {
            x += dx, y += dy;
        }
        return std::pair{-x, -y};
    }();

    void dfs()
    {
        // x and y are unsigned so if we go negative they will become
        // greater than w and h as well
        if (x >= w || y >= h) return;
        if (grid[y][x] == -1) return;
        if (grid[y][x] == 2)
        {
            r += e == l;
            return;
        }

        ++l;
        grid[y][x] = -1;

        for (auto [dx, dy] : kOffsets)
        {
            x += dx, y += dy;
            dfs();
        }

        x += kReset.first, y += kReset.second;  // restore original xy
        grid[y][x] = 0;
        --l;
    }

    u32 uniquePathsIII(std::vector<std::vector<int>>& grid_)
    {
        grid = grid_;
        h = static_cast<u32>(grid.size());
        w = static_cast<u32>(grid[0].size());

        e = 1;  // treat start position as empty
        for (u32 iy = 0; iy != h; ++iy)
        {
            for (u32 ix = 0; ix != w; ++ix)
            {
                if (grid[iy][ix] == 1)
                {
                    x = ix, y = iy;
                }

                e += !grid[iy][ix];
            }
        }

        grid[y][x] = 0;
        dfs();
        return r;
    }
};
