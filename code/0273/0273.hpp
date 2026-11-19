#pragma once

#include <array>
#include <string>

class Solution
{
public:
    static constexpr std::array<std::string_view, 10> kDigits{
        "Zero",
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
    };

    static constexpr std::array<std::string_view, 10> kTeens{
        "Ten",
        "Eleven",
        "Twelve",
        "Thirteen",
        "Fourteen",
        "Fifteen",
        "Sixteen",
        "Seventeen",
        "Eighteen",
        "Nineteen",
    };

    static constexpr std::array<std::string_view, 10> kTens{
        "Twenty",
        "Thirty",
        "Forty",
        "Fifty",
        "Sixty",
        "Seventy",
        "Eighty",
        "Ninety",
    };

    template <size_t div, size_t rem>
    static constexpr size_t take(size_t v)
    {
        return (v / div) % rem;
    };

    static constexpr void belowThousand(size_t v, std::string& out)
    {
        const size_t initial_size = out.size();

        auto add_token = [&](std::string_view token)
        {
            if (initial_size != out.size() || out.size() != 0)
            {
                out += ' ';
            }

            out += token;
        };

        auto add_tokens = [&](auto&&... values)
        {
            (add_token(values), ...);
        };

        if (const size_t h = take<100, 10>(v))
        {
            add_tokens(kDigits[h], "Hundred");
        }

        const size_t t = take<10, 10>(v);
        const size_t d = take<1, 10>(v);
        if (d != 0 || t != 0)
        {
            if (t == 1)
            {
                add_tokens(kTeens[d]);
            }
            else
            {
                if (t != 0) add_token(kTens[t - 2]);
                if (d != 0) add_token(kDigits[d]);
            }
        }
    }

    std::string numberToWords(int num)
    {
        if (num == 0) return "Zero";

        const size_t v = static_cast<size_t>(num);
        std::string s;

        if (size_t k = take<1'000'000'000, 1'000>(v))
        {
            s.append(kDigits[k]);
            s.append(" Billion");
        }

        if (size_t k = take<1'000'000, 1'000>(v))
        {
            belowThousand(k, s);
            s.append(" Million");
        }

        if (size_t k = take<1'000, 1'000>(v))
        {
            belowThousand(k, s);
            s.append(" Thousand");
        }

        if (size_t k = take<1, 1'000>(v))
        {
            belowThousand(k, s);
        }

        return s;
    }
};
