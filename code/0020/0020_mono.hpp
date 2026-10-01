#include <string>

class Solution
{
public:
    inline static char buf[10001];
    bool isValid(std::string& s)
    {
        const size_t n = s.size();
        char inv[128]{1}, t[128]{};
        auto reg = [&](char o, char c)
        {
            inv[o] = inv[c] = c;
            t[o] = static_cast<char>(1 & ~n);
        };
        reg('(', ')'), reg('[', ']'), reg('{', '}');

        size_t i = 0, si = 1;
        while ((t[s[i]] | (inv[buf[si - 1]] == s[i])) & (n + 1 >= si + i))
        {
            char c = s[i++];
            buf[si] = c;
            si += static_cast<size_t>(t[c] - !t[c]);
        };
        return (i == n) & (si == 1);
    }
};
