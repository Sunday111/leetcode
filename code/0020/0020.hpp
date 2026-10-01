#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static char buf[10001]{1};
    bool isValid(std::string& s)
    {
        const size_t n = s.size();
        char inv[128]{};
        u8 t[128]{};
        auto reg = [&](char o, char c)
        {
            inv[o] = c;
            t[o] = !(n & 1);
        };
        reg('(', ')'), reg('[', ']'), reg('{', '}');

        size_t i = 0, si = 1;
        while ((t[s[i]] | (buf[si - 1] == s[i])) & (n + 1 >= si + i))
        {
            char c = s[i++];
            buf[si] = inv[c];
            si += t[c] - !t[c];
        }
        return (i == n) & (si == 1);
    }
};
