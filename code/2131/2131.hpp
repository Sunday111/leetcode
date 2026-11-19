#pragma once

#include <array>
#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int longestPalindrome(
        std::vector<std::string>& words)
    {
        std::array<std::array<uint32_t, 26>, 26> cnt{};

        auto get_cnt = [&cnt](char a, char b) -> uint32_t&
        {
            return cnt[(a - 'a') & 0xFF][(b - 'a') & 0xFF];
        };

        for (auto& s : words) get_cnt(s[0], s[1])++;

        uint32_t r = 0;
        for (char a = 'a'; a != '{'; ++a)
        {
            for (char b = a + 1; b != '{'; ++b)  // NOLINT
            {
                r += 4u * std::min(get_cnt(a, b), get_cnt(b, a));
            }
        }

        bool odd_symmetric = false;
        for (char c = 'a'; c != '{'; ++c)
        {
            auto& v = get_cnt(c, c);
            if (v & 1) odd_symmetric = true;
            r += 4 * (v / 2);
        }

        if (odd_symmetric) r += 2;

        return static_cast<int>(r);
    }
};
