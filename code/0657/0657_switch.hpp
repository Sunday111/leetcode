#pragma once

#include <string_view>

#include "solution_name.hpp"

class LC_SOLUTION_NAME(_switch)
{
public:
    [[nodiscard]] static constexpr bool judgeCircle(std::string_view moves)
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
