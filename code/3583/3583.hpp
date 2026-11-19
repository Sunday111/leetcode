#include <unordered_map>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    static u64 specialTriplets(std::vector<int>& nums)
    {
        std::unordered_map<u32, u32> left, right;
        left.reserve(nums.size() * 2), right.reserve(nums.size() * 2);
        constexpr u32 kMOD = 1'000'000'007;

        u64 r = 0;

        for (int x : nums) ++right[cast<u32>(x)];

        const u64 z = right[0];

        for (int x : nums)
        {
            if (u32 ux = cast<u32>(x))
            {
                --right[ux];
                r += (u64{left[ux * 2]} * u64{right[ux * 2]}) % kMOD;
                ++left[ux];
            }
        }

        // Count zeroes case
        if (z > 2) r += ((z * (z - 1) * (z - 2)) / 6) % kMOD;

        return r % kMOD;
    }
};
