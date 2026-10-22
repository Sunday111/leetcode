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
                           (validPalindrome(s.substr(l + 1, r - l), false) ||
                            validPalindrome(s.substr(l, r - l), false));
                }
            } while (++l < --r);
        }

        return true;
    }
};
