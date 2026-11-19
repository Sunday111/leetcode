#pragma once

#include <string>

class Solution
{
public:
    static constexpr const std::string& reduce(std::string& s)
    {
        size_t n = s.size();
        size_t i = 0;
        size_t j = 0;
        while (j != n)
        {
            if (s[j] == '#')
            {
                if (i != 0) --i;
            }
            else
            {
                if (i != j) s[i] = s[j];
                ++i;
            }

            ++j;
        }

        s.resize(i);
        return s;
    }

    [[nodiscard]] static constexpr bool backspaceCompare(
        std::string& s,
        std::string& t)
    {
        return reduce(s) == reduce(t);
    }
};
