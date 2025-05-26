#pragma once

#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr bool judgeCircle(std::string_view moves)
    {
        int x = 0, y = 0;
        for (char c : moves)
        {
            switch (c)
            {
            case 'U':
                ++y;
                break;
            case 'D':
                --y;
                break;
            case 'R':
                ++x;
                break;
            case 'L':
                --x;
                break;
            }
        }

        return x == 0 && y == 0;
    }
};
