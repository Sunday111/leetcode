#include <algorithm>
#include <cstdint>

using u32 = uint32_t;

class Solution
{
public:
    inline static int memo[20][20];

    static int numTrees(int n, int s = 1)
    {
        if (n < s) return 1;

        int& r = memo[n][s];
        if (r == -1)
        {
            r = 0;
            for (int i = s; i <= n; i++)
            {
                r += numTrees(i - 1, s) * numTrees(n, i + 1);
            }
        }

        return r;
    }
};

inline static const auto kInit = []  // NOLINT
{
    std::fill_n(&Solution::memo[0][0], 20 * 20, -1);
    return true;
}();
