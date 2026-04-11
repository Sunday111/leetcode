#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    int minimumDistance(std::vector<int>& nums_) noexcept
    {
        auto& nums = reinterpret_cast<const std::vector<u32>&>(nums_);
        u32 n = static_cast<u32>(nums.size()), r = 2 * n;
        std::tuple<u32, u32> a[100'001];
        fill_n(a, n + 1, std::tuple{-n, -n});
        for (u32 k = 0; k != n; ++k)
        {
            u32 v = nums[k];
            [[assume(v < 100'001)]];
            auto& [i, j] = a[v];
            r = std::min(r, 2 * (k - i));
            i = j;
            j = k;
        }
        return r < (2 * n) ? static_cast<int>(r) : -1;
    }
};
