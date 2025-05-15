#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
    {
        uint8_t width = static_cast<uint8_t>(matrix.front().size()),
                height = static_cast<uint8_t>(matrix.size());
        uint8_t offset_x = 0, offset_y = 0;

        std::vector<int> r;
        r.reserve(width * height);

        using std::views::reverse;
        auto range = [](uint8_t n)
        {
            return std::views::iota(uint8_t{}, n);
        };

        auto add = [&](uint8_t x, uint8_t y)
        {
            r.push_back(matrix[offset_y + y][offset_x + x]);
        };

        while (true)
        {
            // add top row
            for (auto x : range(width)) add(x, 0);
            ++offset_y;
            if (--height == 0) break;

            // add right column
            for (auto y : range(height)) add(width - 1, y);
            if (--width == 0) break;

            // add bottom row in reverse order
            for (auto x : range(width) | reverse) add(x, height - 1);
            if (--height == 0) break;

            // add left column in reverse order
            for (auto y : range(height) | reverse) add(0, y);
            ++offset_x;
            if (--width == 0) break;
        }

        return r;
    }
};
