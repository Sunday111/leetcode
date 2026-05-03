#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    void rotate(std::vector<std::vector<int>>& m)
    {
        u32 n = m.size() & 0xFF;
        for (u32 ci = 0, t = n - 1, gi = n - 1; ci != n / 2; ++ci, --gi, t -= 2)
        {
            for (u32 i = 0; i != t; ++i)
            {
                int& a = m[ci][ci + i];
                int& b = m[ci + i][gi];
                int& c = m[gi][gi - i];
                int& d = m[gi - i][ci];

                std::swap(a, b);
                std::swap(d, c);
                std::swap(a, c);
            }
        }
    }
};
