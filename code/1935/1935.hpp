#pragma once

#include <bitset>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr int canBeTypedWords(
        std::string_view text,
        std::string_view brokenLetters) noexcept
    {
        std::bitset<32> broken;
        for (char c : brokenLetters) broken[(c - 'a') & 0x1F] = 1;

        bool bad = false;
        int r = 0;
        for (char c : text)
        {
            if (c == ' ')
            {
                r += !bad;
                bad = false;
            }
            else
            {
                bad |= broken[(c - 'a') & 0x1F];
            }
        }

        return r + !bad;
    }
};
