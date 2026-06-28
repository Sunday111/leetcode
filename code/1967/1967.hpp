#include <string>
#include <vector>

#include "integral_aliases.hpp"

void buildLPS(const char* p, u32 m, u32* lps)
{
    u32 l = 0, i = 1;
    lps[0] = 0;
    while (i != m)
    {
        bool eq = p[i] == p[l];
        l += eq;
        lps[i] = l;
        i += eq || !l;
        l += (lps[l - !!l] - l) & (-u32{!eq});
    }
}

bool match(const std::string& s, const char* p, u32 m, const u32* lps)
{
    u32 n = static_cast<u32>(s.size());
    u32 i = 0, j = 0;
    while (i != n && j != m)
    {
        bool eq = s[i] == p[j];
        i += eq || !j;
        j += eq + ((lps[j - !!j] - j) & -u32{!eq});
    }

    return j == m;
}

class Solution
{
public:
    u32 numOfStrings(std::vector<std::string>& patterns, std::string& word)
    {
        u32 lps[100], r = 0;
        for (auto& p : patterns)
        {
            u32 m = static_cast<u32>(p.size());
            buildLPS(p.data(), m, lps);
            r += match(word, p.data(), m, lps);
        }
        return r;
    }
};
