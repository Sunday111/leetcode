#include <string_view>

class Solution
{
public:
    int scoreOfParentheses(std::string_view s) const noexcept
    {
        int d = 0, st[27];
        st[d] = 0;
        for (char c : s)
        {
            bool x = c == '(';
            int m = -!x;
            d += x + m;
            st[d] = (st[d] + std::max(st[d + 1] * 2, 1)) & m;
        }
        return st[0];
    }
};
