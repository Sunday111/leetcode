#pragma once

#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr u16 minAddToMakeValid(
        std::string_view s) noexcept
    {
        u16 o = 0, r = 0;
        for (char c : s)
        {
            if (c == '(')
            {
                ++o;
            }
            else if (o > 0)
            {
                --o;
            }
            else
            {
                ++r;
            }
        }

        return r + o;
    }
};
