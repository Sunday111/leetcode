#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    void rotate(std::vector<std::vector<char>>& m)
    {
        u32 n = cast<u32>(m.size());
        for (u32 ci = 0, t = n - 1, gi = n - 1; ci != n / 2; ++ci, --gi, t -= 2)
        {
            for (u32 i = 0; i != t; ++i)
            {
                auto& a = m[ci][ci + i];
                auto& b = m[ci + i][gi];
                auto& c = m[gi][gi - i];
                auto& d = m[gi - i][ci];

                std::swap(a, b);
                std::swap(d, c);
                std::swap(a, c);
            }
        }
    }
    auto rotateTheBox(std::vector<std::vector<char>>& g)
    {
        u32 h = cast<u32>(g.size()), w = cast<u32>(g[0].size());
        for (auto& r : g)
        {
            for (u32 i = w - 1, j = i; i < w; --i)
            {
                char &ci = r[i], &cj = r[j];
                bool a = ci == '*', b = ci == '#';
                ci = ('.' & -b) | (ci & -!b);  // NOLINT
                cj = ('#' & -b) | (cj & -!b);  // NOLINT
                j = ((i & -u32{a}) | (j & -u32{!a})) - (u32{a} | u32{b});
            }
        }

        if (w == h)
        {
            rotate(g);
            return std::move(g);
        }

        std::vector<std::vector<char>> r;
        r.resize(w);
        for (auto& x : r) x.resize(h);
        for (u32 y = 0; y != h; ++y)
        {
            for (u32 x = 0, t = h - y - 1; x != w; ++x)
            {
                r[x][t] = g[y][x];
            }
        }
        return r;
    }
};
