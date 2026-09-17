#include <algorithm>
#include <bit>
#include <cstdint>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    int minOperations(const std::vector<int>& nums, u32 x) noexcept
    {
        const auto a = reinterpret_cast<const u32*>(nums.data());
        const u32 n = nums.size() & ~u32{};
        u32 ans = ~u32{};

        // Find the shortest prefix whose sum reaches x.
        u32 l = 0, ls = 0;
        while (l != n && ls < x) ls += a[l++];
        ans = std::min(ans, l | -u32{ls != x});

        // Only for this branchless exercise, replace the early exit with masks.
        // An insufficient total sets l = x = 0, skipping both loops; positive
        // suffix sums cannot match zero, preserving the failure sentinel.
        l &= -u32{ls >= x};
        x &= -u32{ls >= x};

        // Trade prefix elements for suffix elements, recording exact sums.
        u32 r = n - 1, rs = a[r];
        while (l)
        {
            u32 s = ls + rs, b = s < x;
            rs += a[r -= b] & -b;
            ans = std::min(ans, (l + n - r) | -u32{s != x});
            ls -= a[l -= !b] & ~-b;
        }

        // Complete the suffix-only candidate.
        while (rs < x) rs += a[--r];
        ans = std::min(ans, (n - r) | -u32{rs != x});

        return std::bit_cast<int>(ans);
    }
};
