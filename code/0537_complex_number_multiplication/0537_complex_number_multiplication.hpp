#pragma once

#include <cassert>
#include <format>
#include <string>

class Solution
{
public:
    struct Complex
    {
        int real;
        int imag;
    };

    [[nodiscard]] static constexpr Complex multiply(
        const Complex& a,
        const Complex& b)
    {
        // (ra + ia * i) * (rb + ib * i)
        // ra * rb + ra * ib * i + rb * ia * i + ia * ib * i * i
        // ra * rb + ra * ib * i + rb * ia * i - ia * ib
        // ra * rb - ia * ib + ra * ib * i + rb * ia * i
        // ra * rb - ia * ib + (ra * ib + rb * ia) * i
        return {
            .real = a.real * b.real - a.imag * b.imag,
            .imag = a.real * b.imag + b.real * a.imag,
        };
    }

    [[nodiscard]] static constexpr Complex parse(const std::string& s)
    {
        size_t i = 0;

        auto get_num = [&]() -> int
        {
            bool negative = s[i] == '-';
            if (negative) ++i;

            int r = 0;
            while (std::isdigit(s[i]))
            {
                r = r * 10 + s[i] - '0';
                ++i;
            }

            return negative ? -r : r;
        };

        int real = get_num();
        assert(s[i] == '+');
        ++i;

        int imag = get_num();
        assert(s[i] == 'i');

        return {.real = real, .imag = imag};
    }

    [[nodiscard]] static constexpr std::string toString(const Complex& v)
    {
        return std::format("{}+{}i", v.real, v.imag);
    }

    std::string complexNumberMultiply(
        const std::string& num1,
        const std::string& num2)
    {
        auto a = parse(num1);
        auto b = parse(num2);
        auto r = multiply(a, b);
        return toString(r);
    }
};
