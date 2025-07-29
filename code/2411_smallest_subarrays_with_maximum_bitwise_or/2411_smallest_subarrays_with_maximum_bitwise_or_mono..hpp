#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <vector>





using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> smallestSubarrays(
        std::vector<int>& nums) noexcept
    {
        const int target =
            std::accumulate(nums.begin(), nums.end(), 0, std::bit_or{});

        const u32 n = static_cast<u32>(nums.size());
        std::array<u32, 32> counters{};

        u32 i = 0, j = 0;
        if (target != 0)
        {
            int acc = 0;
            while (j != n)
            {
                int v = nums[j];
                acc |= v;

                for (u8 k = 0; k != 32; ++k)
                {
                    if (v & (1 << k))
                    {
                        ++counters[k];
                    }
                }

                ++j;

                if (acc == v)
                {
                    v = nums[i];
                    for (u8 k = 0; k != 32; ++k)
                    {
                        if (((v & (1 << k)) != 0) && (--counters[k] == 0))
                        {
                            acc &= ~(1 << k);
                        }
                    }

                    nums[i] = static_cast<int>(j - i);

                    ++i;
                }
            }
        }

        std::ranges::fill_n(nums.begin() + i, n - i, 1);
        return std::move(nums);
    }
};
