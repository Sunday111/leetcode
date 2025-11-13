#pragma once

#include <ranges>
#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr int maxOperations(
        const std::string& s) noexcept
    {
        int a = 0, z = 0, p = 1;
        for (auto c : std::views::reverse(s))
        {
            int m = (c == '0') - 1;
            a += z & m;
            z += p & ~m;
            p = m & 1;
        }
        return a;
    }
};
