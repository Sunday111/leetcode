#pragma once

#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;

    [[nodiscard]] static constexpr bool isOptionalExponent(std::string_view s)
    {
        if (s.empty()) return true;
        if (std::tolower(s.front()) != 'e') return false;
        s.remove_prefix(1);
        if (s.empty()) return false;
        return isInteger(s, true);
    }

    [[nodiscard]] static constexpr std::string_view parseDigits(
        std::string_view s) noexcept
    {
        u8 i = 0;
        while (i != s.size() && std::isdigit(s[i])) ++i;
        return s.substr(0, i);
    }

    [[nodiscard]] static constexpr bool isInteger(
        std::string_view s,
        bool parsing_exp = false) noexcept
    {
        if (s.empty()) return false;
        s.remove_prefix(s[0] == '+' || s[0] == '-');
        auto digits = parseDigits(s);
        if (digits.empty()) return false;
        s.remove_prefix(digits.size());
        if (parsing_exp) return s.empty();
        return isOptionalExponent(s);
    }

    [[nodiscard]] static constexpr bool isDecimal(std::string_view s) noexcept
    {
        s.remove_prefix(s[0] == '+' || s[0] == '-');
        auto lead_digits = parseDigits(s);
        s.remove_prefix(lead_digits.size());

        if (!s.empty() && s[0] == '.')
        {
            s.remove_prefix(1);
            auto after_dot = parseDigits(s);
            s.remove_prefix(after_dot.size());
            if (lead_digits.size() + after_dot.size() == 0) return false;
        }
        else if (lead_digits.empty())
        {
            return false;
        }

        return isOptionalExponent(s);
    }

    [[nodiscard]] static constexpr bool isNumber(std::string_view s) noexcept
    {
        return isInteger(s) || isDecimal(s);
    }
};
