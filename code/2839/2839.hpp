// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/

#include <ranges>
#include <string>

#include "all_equal_to.hpp"

class Solution
{
public:
    [[nodiscard]] constexpr bool canBeEqual(
        const std::string& s1,
        const std::string& s2) noexcept
    {
        int f[2][26]{};
        for (bool i = 0; auto [a, b] : std::views::zip(s1, s2))
        {
            ++f[i][a - 'a'];
            --f[i][b - 'a'];
            i = !i;
        }

        return all_equal_to(f[0], 0) && all_equal_to(f[1], 0);
    }
};
