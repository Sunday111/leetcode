#include <bit>
#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    int numberOfSpecialChars(std::string& word)
    {
        u32 b[2]{};
        for (char c : word)
        {
            bool t = c < 'a';
            b[t] |= u32{1} << (c - ('a' - (t << 5)));
        }
        return std::popcount(b[0] & b[1]);
    }
};
