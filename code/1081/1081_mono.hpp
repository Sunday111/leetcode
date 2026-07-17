#include <bitset>
#include <string>


class Solution
{
public:
    using u32 = uint32_t;
    std::string smallestSubsequence(std::string& s)
    {
        u32 f[27]{};
        u32 nr = 0, k1 = 0, n = static_cast<u32>(s.size());
        std::bitset<32> b;

        for (char c : s)
        {
            ++f[c - 'a'];
            b[(c - 'a') & 0xFF] = 1;
        }

        s[n] = 'a' + 26;
        u32 stop = b.count() & 0xFF;
        b = {};

        while ((k1 != n) & (stop != b.count()))
        {
            u32 ci = s[k1] & 0xFF, i = ci - 'a';
            auto k2 = std::min(nr - 1, n);
            u32 cj = s[k2] & 0xFF, j = cj - 'a';
            bool t1 = b[i];
            bool t = (ci < cj) & !!f[j];
            bool np = !(t & !t1);
            k1 += np;
            f[i] -= np;
            b[j] = b[j] & np;
            b[i] = np;
            s[nr] = static_cast<char>(ci);
            nr += !(t1 | t) - !np;
        }

        s.resize(nr);
        return std::move(s);
    }
};
