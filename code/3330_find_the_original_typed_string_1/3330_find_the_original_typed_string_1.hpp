#pragma once

#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr int possibleStringCount(
        std::string_view word) noexcept
    {
        u8 n = word.size() & 0xFF, count = n;
        for (u8 i = 1; i != n; ++i)
        {
            if (word[i] != word[i - 1]) --count;
        }
        return count;
    }
};
