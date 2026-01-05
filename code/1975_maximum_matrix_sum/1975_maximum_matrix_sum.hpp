#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto maxMatrixSum(
        const std::vector<std::vector<int>>& matrix) noexcept
    {
        long long s = 0;
        int n = 0, t = std::numeric_limits<int>::max();
        for (auto& r : matrix)
        {
            for (auto& x : r)
            {
                int a = abs(x);
                n ^= (x < 0);
                t = std::min(t, a);
                s += a;
            }
        }
        return s - ((2 * t) & -n);
    }
};
