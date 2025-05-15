#pragma once

#include <ranges>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        uint8_t width = static_cast<uint8_t>(n),
                height = static_cast<uint8_t>(n);
        uint8_t offset_x = 0, offset_y = 0;

        using std::views::reverse;
        auto range = [](uint8_t n)
        {
            return std::views::iota(uint8_t{}, n);
        };

        int next_number = 0;
        std::vector m(height, std::vector<int>(width, 0));
        auto add = [&](uint8_t x, uint8_t y)
        {
            m[offset_y + y][offset_x + x] = ++next_number;
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

        return m;
    }
};
