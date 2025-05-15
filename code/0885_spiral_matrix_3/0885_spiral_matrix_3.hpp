#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr static std::vector<std::vector<int>>
    spiralMatrixIII(
        uint8_t height,
        uint8_t width,
        uint8_t y0,
        uint8_t x0) noexcept
    {
        std::vector<std::vector<int>> result;
        result.reserve(width * height);

        auto write = [&](uint8_t x, uint8_t y)
        {
            result.emplace_back(std::vector<int>{y, x});
        };

        write(x0, y0);

        uint8_t local_w = 1, local_h = 1;
        uint8_t x_offset = x0, y_offset = y0;

        using std::views::reverse;
        auto range = [](uint8_t n)
        {
            return std::views::iota(uint8_t{}, n);
        };

        while (local_w < width || local_h < height)
        {
            if (uint8_t x = x_offset + local_w; x != width)
            {
                local_w += 1;
                for (auto local_y : range(local_h))
                {
                    write(x, y_offset + local_y);
                }
            }

            if (uint8_t y = y_offset + local_h; y != height)
            {
                local_h += 1;
                for (auto local_x : range(local_w) | reverse)
                {
                    write(x_offset + local_x, y);
                }
            }

            if (x_offset != 0)
            {
                --x_offset;
                ++local_w;
                for (auto local_y : range(local_h) | reverse)
                {
                    write(x_offset, y_offset + local_y);
                }
            }

            if (y_offset != 0)
            {
                --y_offset;
                ++local_h;
                for (auto local_x : range(local_w))
                {
                    write(x_offset + local_x, y_offset);
                }
            }
        }

        return result;
    }
};
