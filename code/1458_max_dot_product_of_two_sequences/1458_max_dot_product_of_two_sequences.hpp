#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr int maxDotProduct(
        const std::vector<int>& va,
        const std::vector<int>& vb) noexcept
    {
        int prev[500], curr[500];
        const u16 lim_i = va.size() & 0xFFFF, lim_j = vb.size() & 0xFFFF;

        curr[0] = va[0] * vb[0];
        for (u16 j = 1; j != lim_j; ++j)
        {
            curr[j] = std::max(curr[j - 1], va[0] * vb[j]);
        }

        for (u16 i = 1; i != lim_i; ++i)
        {
            int a = va[i];
            std::swap(curr, prev);
            curr[0] = std::max(prev[0], a * vb[0]);

            for (u16 j = 1; j != lim_j; ++j)
            {
                int o1 = a * vb[j];         // just ab
                int o2 = prev[j - 1] + o1;  // take ab
                int o3 = prev[j];           // ignore i
                int o4 = curr[j - 1];       // ignore j
                curr[j] = std::max(std::max(o1, o2), std::max(o3, o4));
            }
        }

        return curr[lim_j - 1];
    }
};
