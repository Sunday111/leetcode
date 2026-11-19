#pragma once

#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto divisibilityArray(
        const std::string& word,
        const uint32_t m) noexcept
    {
        std::vector<int> r;
        r.reserve(word.size());

        uint64_t v = 0;
        for (char c : word)
        {
            uint8_t digit = (c - '0') & 0xFF;
            v *= 10;
            v += digit;
            v %= m;
            r.emplace_back(v == 0);
        }

        return r;
    }
};
