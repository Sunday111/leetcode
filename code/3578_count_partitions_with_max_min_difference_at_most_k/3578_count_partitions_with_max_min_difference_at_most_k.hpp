#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static u32 countPartitions(
        const std::vector<int>& nums_,
        u32 k) noexcept
    {
        constexpr u32 N = 50'001, kMOD = 1'000'000'007;
        static u32 qMax[N], qMin[N], sum[N + 2];
        auto nums = reinterpret_cast<const u32*>(nums_.data());
        u32 frontX = 1, frontN = 1, backX = 0, backN = 0;
        sum[0] = 0;
        sum[1] = 1;

        u32 cnt = 0;
        for (u32 l = 0, r = 0; r < nums_.size(); r++)
        {
            u32 x = nums[r];

            while (backX >= frontX && nums[qMax[backX]] <= x) backX--;
            qMax[++backX] = r;

            while (backN >= frontN && nums[qMin[backN]] >= x) backN--;
            qMin[++backN] = r;

            while (nums[qMax[frontX]] - nums[qMin[frontN]] > k)
            {
                frontX += (qMax[frontX] == l);
                frontN += (qMin[frontN] == l);
                l++;
            }

            cnt = (kMOD + sum[r + 1] - sum[l]) % kMOD;
            sum[r + 2] = (sum[r + 1] + cnt) % kMOD;
        }
        return cnt;
    }
};
