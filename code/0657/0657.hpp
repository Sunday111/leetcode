#pragma once

#include <string_view>

#include "solution_name.hpp"

class LC_SOLUTION_NAME(_branchless)
{
public:
    [[nodiscard]] static constexpr bool judgeCircle(std::string_view moves) noexcept
    {
        int x = 0, y = 0;
        for (char c : moves)
        {
            y += (c == 'U') - (c == 'D');
            x += (c == 'R') - (c == 'L');
        }

        return x == 0 && y == 0;
    }
};
