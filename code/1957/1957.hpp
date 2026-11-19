#pragma once

#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string makeFancyString(
        std::string& s) noexcept
    {
        char p = 0;
        uint32_t l = 0, k = 1;
        for (char c : s)
        {
            k = (p == c) ? k + 1 : 1;
            p = c;
            if (k < 3) s[l++] = p;
        }
        s.resize(l);
        return s;
    }
};
