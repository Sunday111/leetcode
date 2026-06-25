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
            // clang-format off
            x += f[t] & -u32{b};
            t +=  b; bool bhi = t > hi; hi += bhi; f[t] &= -u32{!bhi};
            t -= !b; bool blo = t < lo; lo -= blo; f[t] &= -u32{!blo};
            x -= f[t] & -u32{!b};
            // clang-format on
            ++f[t];
            r += x;
        }
        return r;
    }
};
