#pragma once

#include <format>
#include <string>

class Solution
{
public:
    std::string solveEquation(const std::string& s)
    {
        bool left_part = true;
        int kx = 0;
        int sum = 0;

        size_t i = 0;
        while (i != s.size())
        {
            if (s[i] == '=')
            {
                ++i;
                left_part = false;
                continue;
            }

            bool negative = false;

            if (s[i] == '-')
            {
                negative = true;
                ++i;
            }
            else if (s[i] == '+')
            {
                ++i;
            }

            int v = 0;
            if (s[i] == 'x')
            {
                v = 1;
            }
            else
            {
                while (std::isdigit(s[i]) && i != s.size())
                {
                    v = v * 10 + (s[i] - '0');
                    ++i;
                }
            }

            if (negative) v = -v;

            if (s[i] == 'x')
            {
                ++i;
                if (!left_part) v = -v;
                kx += v;
            }
            else
            {
                if (left_part) v = -v;
                sum += v;
            }
        }

        if (kx == 0)
        {
            if (sum == 0)
            {
                return "Infinite solutions";
            }

            return "No solution";
        }

        return std::format("x={}", sum / kx);
    }
};
