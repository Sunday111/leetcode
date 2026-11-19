#pragma once

#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr char kthCharacter(size_t k) noexcept
    {
        std::string s = "a";
        --k;
        while (k >= s.size())
        {
            s.reserve(s.size() * 2);
            size_t n = s.size();
            for (size_t i = 0; i != n; ++i)
            {
                s.push_back(static_cast<char>(s[i] + 1));
            }
        }

        return s[k];
    }
};
