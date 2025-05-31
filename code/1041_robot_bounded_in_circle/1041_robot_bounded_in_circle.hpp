#pragma once

#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isRobotBounded(
        const std::string& instructions)
    {
        int x{}, y{}, dx{}, dy{1};
        for (char c : instructions)
        {
            switch (c)
            {
            case 'L':
                std::swap(dx, dy);
                dx = -dx;
                break;
            case 'R':
                std::swap(dx, dy);
                dy = -dy;
                break;
            case 'G':
                x += dx, y += dy;
                break;
            }
        }

        // Robot escapes the circle if after all instructions
        // it has the same direction and did not come back
        // to the origin
        return dx || dy != 1 || !(x | y);
    }
};
