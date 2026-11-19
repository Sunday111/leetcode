#pragma once

#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string largestGoodInteger(
        std::string& num) noexcept
    {
        uint16_t i{}, j = 1, n = static_cast<uint16_t>(num.size());
        char c = 0;
        while (j != n)
        {
            bool a = num[i] == num[j], b = j == i + 2, t = a && !b;
            j += t, i += !t;
            c = std::max(c, static_cast<char>(num[i] * (a && b)));
        }

        if (!c) return "";
        num = {c, c, c};
        return std::move(num);
    }
};
