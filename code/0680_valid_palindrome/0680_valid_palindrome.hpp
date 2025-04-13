#pragma once

#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr bool validPalindrome(
        std::string_view s,
        bool allow_one_mistake = true)
    {
        if (s.size() > 1)
        {
            size_t l = 0, r = s.size() - 1;
            do
            {
                if (s[l] != s[r])
                {
                    return allow_one_mistake &&
                           (validPalindrome({&s[l + 1], &s[r + 1]}, false) ||
                            validPalindrome({&s[l], &s[r]}, false));
                }
            } while (++l < --r);
        }

        return true;
    }
};
