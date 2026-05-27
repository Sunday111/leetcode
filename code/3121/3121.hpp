#include <bit>
#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    int numberOfSpecialChars(const std::string& word) noexcept
    {
        u32 p[2]{}, bad{};
        for (char c : word)
        {
            bool l = c > 'Z';             // is lower case?
            auto i = c - 'A' - (l << 5);  // index in alphabet
            [[assume(i < 26)]];           // a promise to the compiler
            bad |= (u32{l} << i) & p[0];  // met lower after upper
            p[l] |= 1 << i;               // mark as visited
        }

        // both cases visited and not marked as bad
        return std::popcount(p[0] & p[1] & ~bad);
    }
};

#include "sync_stdio.hpp"
