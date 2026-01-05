#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr auto countMajoritySubarrays(
        const std::vector<int>& nums,
        int target) noexcept
    {
        using u16 = uint16_t;
        const u16 n = nums.size() & 0xFFFF, n1 = n + 1;

        u16 f[1001];
        for (u16 i = 1, t = 0; int x : nums)
        {
            t += x == target;
            f[i++] = t;
        }

        unsigned r = 0;
        for (u16 i = 0; f[i] != f[n]; ++i)
        {
            for (u16 l = 1, j = i + 1; j != n1; ++j, ++l)
            {
                r += l / 2 < (f[j] - f[i]);
            }
        }

        return r;
    }
};
