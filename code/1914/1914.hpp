#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    [[nodiscard]] static constexpr std::vector<std::vector<int>> rotateGrid(
        std::vector<std::vector<int>> grid,
        const u32 k) noexcept
    {
        const u32 h = static_cast<u32>(grid.size());
        const u32 w = static_cast<u32>(grid.front().size());
        const u32 num_layers = std::min(w, h) / 2;

        std::vector<int> layer_values;
        layer_values.reserve((std::max(w, h) - 1) * 4);

        for (u32 layer = 0; layer != num_layers; ++layer)
        {
            const u32 hs = (w - layer * 2) - 1;
            const u32 vs = (h - layer * 2) - 1;
            const u32 layer_size = 2 * (hs + vs);
            const u32 lk = k % layer_size;
            const u32 first_y = layer, last_y = first_y + vs;
            const u32 first_x = layer, last_x = first_x + hs;

            auto value_at = [&](u32 li) -> auto&
            {
                if (li < vs) return grid[first_y + li][first_x];
                li -= vs;
                if (li < hs) return grid[last_y][first_x + li];
                li -= hs;
                if (li < vs) return grid[last_y - li][last_x];
                li -= vs;
                return grid[first_y][last_x - li];
            };

            layer_values.resize(layer_size);
            for (u32 i = 0; i != layer_size; ++i)
            {
                layer_values[(i + lk) % layer_size] = value_at(i);
            }

            for (u32 i = 0; i != layer_size; ++i)
            {
                value_at(i) = layer_values[i];
            }
        }

        return grid;
    }
};
