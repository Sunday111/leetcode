#pragma once

#include <format>
#include <string>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string fizzBuzzI(int i)
    {
        bool k_3 = (i % 3) == 0;
        bool k_5 = (i % 5) == 0;
        if (k_3 && k_5) return "FizzBuzz";
        if (k_3) return "Fizz";
        if (k_5) return "Buzz";
        return std::format("{}", i);
    }

    [[nodiscard]] static constexpr std::vector<std::string> fizzBuzz(int n)
    {
        std::vector<std::string> r;
        r.reserve(static_cast<size_t>(n));

        int i = 0;
        do
        {
            ++i;
            r.push_back(fizzBuzzI(i));
        } while (i != n);

        return r;
    }
};
