#pragma once

#include <cstdint>
#include <numeric>
#include <vector>

class Solution
{
public:
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using i64 = int64_t;
    [[nodiscard]] static constexpr i64 largestPerimeter(
        std::vector<int>& nums) noexcept
    {
        constexpr u32 base = 256U;
        constexpr i32 mask = base - 1U;

        const u32 n = static_cast<u32>(nums.size());
        static i32 sort_buffer[100'001];  // NOLINT

        {
            i32* buffer = sort_buffer;
            i32* data = nums.data();
            for (u32 pass = 0; pass != 4; ++pass)
            {
                std::array<u32, base> count{};
                const u32 shift = pass * 8U;

                // Count occurrences
                for (u32 i = 0; i < n; ++i)
                {
                    // NOLINTNEXTLINE
                    ++count[(data[i] >> shift) & mask];
                }

                // Convert counts to absolute positions
                u32 pos = 0U;
                for (u32 i = 0; i < base; ++i)
                {
                    const u32 tmp = count[i];
                    count[i] = pos;
                    pos += tmp;
                }

                // Placement (unstable)
                for (u32 i = 0; i < n; ++i)
                {
                    // NOLINTNEXTLINE
                    buffer[count[(data[i] >> shift) & mask]++] = data[i];
                }

                // Swap for next pass
                std::swap(data, buffer);
            }
        }

        i64 sum = std::accumulate(nums.begin(), nums.end(), i64{});
        u32 i = n - 1;
        while (i != 1 && sum <= 2 * nums[i]) sum -= nums[i--];
        return i > 1 ? sum : -1;
    }
};
