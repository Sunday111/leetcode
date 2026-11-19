#pragma once

#include <array>
#include <bitset>
#include <string>

class Solution
{
public:
    static constexpr auto is_vowel = []
    {
        std::bitset<128> bs;
        for (char c : "aeiouAEIOU") bs[c & 0x7F] = 1;
        return bs;
    }();

    [[nodiscard]] static constexpr std::string sortVowels(
        std::string s) noexcept
    {
        std::array<int, 128> freq{};
        for (char c : s) ++freq[c & 0x7F];
        uint8_t next = 'A';
        for (char& c : s)
        {
            if (!is_vowel[c & 0x7F]) continue;
            while (!is_vowel[next] || freq[next] == 0) ++next;
            freq[next]--;
            c = static_cast<char>(next);
        }

        return s;
    }
};
