
#include <algorithm>
#include <numeric>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    static constexpr int lt = -1, eq = 0, gt = 1;

    struct Seq
    {
        int cmp = 0;
        u32 begin = 0;
        u32 end = 0;
        i64 suffix = 0;
    };

    i64 maxSumTrionic(std::vector<i32>& nums) noexcept
    {
        const u32 n = static_cast<u32>(nums.size());

        static i64 p[100'001];
        std::exclusive_scan(nums.begin(), nums.end(), p, i64{0}, std::plus{});
        p[n] = p[n - 1] + nums[n - 1];

        i64 ans = std::numeric_limits<i64>::min();
        Seq oldest{}, old{}, curr{};

        auto close_seq = [&](u32 end)
        {
            curr.end = end;

            if (curr.cmp == gt && old.cmp == lt && oldest.cmp == gt)
            {
                i64 mid = p[old.end] - p[old.begin];
                i64 left = oldest.suffix + std::min(0, nums[oldest.end - 2]);
                i64 right = nums[curr.begin + 1] +
                            std::max<i64>(0, p[curr.end] - p[curr.begin + 2]);
                ans = std::max(ans, left + mid + right);
            }

            oldest = old;
            old = curr;
        };

        i32 prev = nums[0];

        for (u32 i = 1; i != n; ++i)
        {
            i32 v = nums[i];

            if (auto k = std::clamp(v - prev, -1, 1); curr.cmp != k)
            {
                i32 m = std::max(0, nums[i - 1]);
                curr.suffix -= m;
                close_seq(i);
                curr = {.cmp = k, .begin = i - 1, .suffix = m};
            }

            curr.suffix += std::max(0, nums[i]);
            prev = v;
        }

        close_seq(n);

        return ans;
    }
};
