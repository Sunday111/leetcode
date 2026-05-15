#include <vector>


class Solution
{
public:
    bool isGood(const std::vector<int>& a)
    {
        int f[201]{};
        int nt = 0, t = 0;
        int n = static_cast<int>(a.size() - 1), m = 0;
        for (int x : a)
        {
            int c = ++f[x];
            nt += c > 1;
            if (c > 1) t = x;
            m = std::max(m, x);
        }

        return m == n && nt == 1 && m == t;
    }
};
