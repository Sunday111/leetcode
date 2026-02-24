#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int scoreDifference(
        const std::vector<int>& nums) noexcept
    {
        int p[2]{0, 0};
        for (int t = 0, a = 0; int score : nums)
        {
            a ^= ((++t == 6) ^ (score & 1));
            t &= -(t != 6);
            p[a] += score;
        }
        return p[0] - p[1];
    }
};
