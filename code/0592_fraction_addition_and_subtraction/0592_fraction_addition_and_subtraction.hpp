#pragma once

#include <cassert>
#include <format>
#include <numeric>
#include <string>

class Solution
{
public:
    struct Fraction
    {
        int numerator{};
        int denominator{};
    };

    template <typename Callback>
    static constexpr void Parse(const std::string& s, Callback cb)
    {
        size_t i = 0;

        auto get_num = [&]() -> int
        {
            int r = 0;
            while (std::isdigit(s[i]))
            {
                r = r * 10 + s[i] - '0';
                ++i;
            }

            return r;
        };

        Fraction f;
        while (i != s.size())
        {
            bool negative = false;
            if (s[i] == '+')
            {
                ++i;
            }
            else if (s[i] == '-')
            {
                negative = true;
                ++i;
            }

            f.numerator = get_num();
            if (negative) f.numerator = -f.numerator;
            assert(i != s.size() && s[i] == '/');
            ++i;
            f.denominator = get_num();
            cb(f);
        }
    }

    [[nodiscard]] static constexpr std::string toString(const Fraction& f)
    {
        return std::format("{}/{}", f.numerator, f.denominator);
    }

    [[nodiscard]] static constexpr Fraction add(
        const Fraction& a,
        const Fraction& b)
    {
        const int lcm = std::lcm(a.denominator, b.denominator);
        return {
            .numerator = a.numerator * (lcm / a.denominator) +
                         b.numerator * (lcm / b.denominator),
            .denominator = lcm,
        };
    }

    [[nodiscard]] static constexpr Fraction reduce(const Fraction& v)
    {
        const int gcd = std::gcd(v.numerator, v.denominator);
        return {
            .numerator = v.numerator / gcd,
            .denominator = v.denominator / gcd,
        };
    }

    [[nodiscard]] static constexpr std::string fractionAddition(
        const std::string& expression)
    {
        Fraction r{.numerator = 0, .denominator = 1};

        Parse(
            expression,
            [&](const Fraction& arg) { r = reduce(add(r, arg)); });

        return toString(r);
    }
};
