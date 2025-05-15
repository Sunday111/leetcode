#pragma once

#include <algorithm>
#include <cassert>
#include <ranges>
#include <string>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr static uint8_t char_to_int(char c)
    {
        return static_cast<uint8_t>(c - '0');
    }

    [[nodiscard]] constexpr static char int_to_char(uint8_t d)
    {
        return static_cast<char>('0' + d);
    }

    constexpr static auto reverse_digits =
        std::views::reverse | std::views::transform(char_to_int);

    [[nodiscard]] constexpr static std::string multiply(
        const std::string_view a,
        const std::string_view b)
    {
        if (a.front() == '0' || b.front() == '0')
        {
            return "0";
        }

        if (a.size() > b.size()) return multiply(b, a);

        std::string r;
        r.resize(a.size() + b.size(), '0');

        uint8_t a_index = 0;
        for (auto a_digit : a | reverse_digits)
        {
            uint8_t carry = 0;
            uint8_t b_index = a_index;
            for (auto b_digit : b | reverse_digits)
            {
                auto& rc = r[b_index++];
                uint8_t tmp = a_digit * b_digit + carry + char_to_int(rc);
                rc = int_to_char(tmp % 10);
                carry = tmp / 10;
            }

            r[b_index] = int_to_char(carry % 10);
            a_index++;
        }

        while (r.back() == '0') r.pop_back();

        std::ranges::reverse(r);

        return r;
    }
};
