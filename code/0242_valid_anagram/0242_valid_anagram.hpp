#pragma once

#include <array>
#include <cstdint>
#include <string_view>

class Solution
{
public:
    static constexpr bool isAnagram(std::string_view s, std::string_view t)
    {
        if (s.size() != t.size()) return false;

        std::array<int32_t, 26> counters{};
        uint8_t num_negative = 0;

        auto char_counter = [&](char c) -> int32_t&
        {
            return counters[static_cast<uint8_t>(c - 'a')];
        };

        for (char c : s)
        {
            if (char_counter(c)-- == 0) ++num_negative;
        }

        for (char c : t)
        {
            if (++char_counter(c) == 0) --num_negative;
        }

        return num_negative == 0;
    }
};
