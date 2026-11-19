#pragma once

#include <algorithm>
#include <bitset>
#include <string_view>

class Solution
{
public:
    static constexpr auto is_vowel_b = []
    {
        std::bitset<128> r;
        for (char c : "aeiou") r[c & 0x7F] = 1;
        return r;
    }();

    static constexpr bool is_vowel(char c) noexcept
    {
        return is_vowel_b[c & 0x7F];
    }

    static constexpr bool doesAliceWin(std::string_view s) noexcept
    {
        return std::ranges::any_of(s, is_vowel);
    }
};
