#pragma once

#include <algorithm>
#include <array>
#include <string_view>
#include <vector>

class Solution
{
public:
    static constexpr std::vector<int> findAnagrams(
        std::string_view s,
        std::string_view p)
    {
        std::vector<int> r;
        const uint16_t ss = static_cast<uint16_t>(s.size());
        const uint16_t ps = static_cast<uint16_t>(p.size());

        if (ps <= ss)
        {
            uint8_t num_negative = 0;
            std::array<int32_t, 26> counters{};

            auto char_counter = [&](char c) -> int32_t&
            {
                return counters[static_cast<uint8_t>(c - 'a')];
            };

            auto add_char = [&](char c)
            {
                if (++char_counter(c) == 0) --num_negative;
            };

            auto remove_char = [&](char c)
            {
                if (char_counter(c)-- == 0) ++num_negative;
            };

            auto check_count = [&](uint16_t i)
            {
                if (num_negative == 0) r.push_back(i);
            };

            std::ranges::for_each(p, remove_char);
            std::ranges::for_each(s.substr(0, ps), add_char);
            check_count(0);

            uint16_t i = 0, j = ps;
            while (j != ss)
            {
                remove_char(s[i++]);
                add_char(s[j++]);
                check_count(i);
            }
        }

        return r;
    }
};
