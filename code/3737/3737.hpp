#include <vector>

#include "sync_stdio.hpp"

class Solution
{
public:
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;
    inline static u32 f[200'001];

    [[nodiscard]] auto countMajoritySubarrays(
        const std::vector<int>& nums,
        int target) noexcept
    {
        u64 r = 0;
        u32 t = 100'000, x = 0, lo = t, hi = t;
        f[t] = 1;
        for (auto v : nums)
        {
            bool b = v == target;
            x += f[t] & -u32{b};
            t += b;
            f[t] &= -u32{(t <= hi) && (t >= lo)};
            t -= !b;
            f[t] &= -u32{(t <= hi) && (t >= lo)};
            x -= f[t] & -u32{!b};
            ++f[t];
            r += x;
            lo = std::min(lo, t);
            hi = std::max(hi, t);
        }
        return r;
    }
};
