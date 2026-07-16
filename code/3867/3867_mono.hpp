#include <algorithm>
#include <numeric>
#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

    static u64 gcdSum(u32* __restrict__ nums, const u32 n) noexcept
    {
        u32 m = nums[0];
        for (u32 i = 1; i != n; ++i)
        {
            u32 v = nums[i];
            m = std::max(m, v);
            nums[i] = std::gcd(v, m);
        }

        u64 r = 0;
        std::ranges::sort(nums, nums + n);
        for (u32 i = 0, j = n - 1; i < j; ++i, --j)
        {
            r += std::gcd(nums[i], nums[j]);
        }

        return r;
    }

    u64 gcdSum(std::vector<int>& nums)
    {
        // NOLINTNEXTLINE
        return gcdSum(
            reinterpret_cast<u32*>(nums.data()),
            static_cast<u32>(nums.size()));
    }
};
