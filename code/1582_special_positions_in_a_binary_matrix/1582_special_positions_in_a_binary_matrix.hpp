#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    int numSpecial(const std::vector<std::vector<int>>& m)
    {
        u8 h = m.size() & 0xFF, w = m[0].size() & 0xFF;
        std::vector<u8> sr(h, 0), sc(w, 0);
        for (u8 y = 0; y != h; ++y)
        {
            auto& row = m[y];
            auto& sry = sr[y];
            for (u8 x = 0; x != w; ++x)
            {
                u8 v = row[x] & 1;
                sry += v;
                sc[x] += v;
            }
        }

        u8 r = 0;
        for (u8 y = 0; y != h; ++y)
        {
            if (sr[y] != 1) continue;
            auto& row = m[y];
            u8 x = 0;
            while (!row[x]) ++x;
            r += sc[x] == 1;
        }
        return r;
    }
};
