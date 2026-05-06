#include <vector>

class Solution
{
public:
    auto maxValue(std::vector<int>& a) noexcept
    {
        static int p[100000];
        auto d = a.data();
        const int n = static_cast<int>(a.size());
        [[assume(n < 100001)]];

        for (int i = 0, t = 0; i != n; ++i)
        {
            p[i] = t = std::max(t, d[i]);
        }

        for (int i = n, ps = p[n - 1], pa = 0; i--;)
        {
            bool b = p[i] > std::exchange(ps, std::min(d[i], ps));
            pa = d[i] = ((pa & -b) | (p[i] & -!b));
        }

        return std::move(a);
    }
};
