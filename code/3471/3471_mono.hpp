#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    int largestInteger(const std::vector<int>& a, u32 k) noexcept
    {
        const u32 n = static_cast<u32>(a.size());
        [[assume(n <= 50)]];
        [[assume(k <= n)]];

        u32 f[51]{};

        for (u32 i = 0; i != k; ++i)
        {
            f[a[i]] = 1;
        }

        for (u32 i = k; i++ != n;)
        {
            for (u32 j = i - k; j != i; ++j)
            {
                ++f[a[j]];
            }
        }

        for (int i = 51; i--;)
        {
            if (f[i] == 1)
            {
                return i;
            }
        }

        return -1;
    }
};
