#include <algorithm>
#include <cstdint>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;
    [[nodiscard]] static constexpr u64 maxAlternatingSum(
        const std::vector<int>& nums) noexcept
    {
        u32 freq[40001], num_negative = static_cast<u32>(nums.size() / 2),
                         min_x = static_cast<u32>(std::abs(nums[0])),
                         max_x = min_x;
        freq[min_x] = 0;
        for (int v : nums)
        {
            u32 x = static_cast<u32>(std::abs(v));
            while (x < min_x) freq[--min_x] = 0;
            while (x > max_x) freq[++max_x] = 0;
            ++freq[x];
        }

        u32 i = min_x;
        u64 s = 0;

        while (num_negative)
        {
            u32& f = freq[i];
            u32 t = std::min(num_negative, f);
            num_negative -= t;
            f -= t;
            s -= u64{i} * u64{i} * u64{t};
            i += (f == 0);
        }

        for (u32 i_end = max_x + 1; i != i_end; ++i)
        {
            s += u64{i} * u64{i} * u64{freq[i]};
        }

        return s;
    }
};
