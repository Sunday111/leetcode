#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>>
    matrixReshape(std::vector<std::vector<int>>& m, size_t height, size_t width)
    {
        size_t old_height = m.size();
        size_t old_width = m.front().size();

        if (old_width * old_height != width * height)
        {
            return std::move(m);
        }

        size_t next_y = 0;
        size_t next_x = 0;

        auto get_next = [&]
        {
            auto v = m[next_y][next_x];
            if (++next_x == old_width)
            {
                next_x = 0;
                ++next_y;
            }
            return v;
        };

        std::vector<std::vector<int>> r;
        r.reserve(height);

        for (size_t y = 0; y != height; ++y)
        {
            auto& row = r.emplace_back();
            row.reserve(width);

            for (size_t x = 0; x != width; ++x)
            {
                row.push_back(get_next());
            }
        }

        return r;
    }
};
