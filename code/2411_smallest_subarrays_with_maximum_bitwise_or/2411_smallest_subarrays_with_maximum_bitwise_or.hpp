#pragma once

#include <array>
#include <bit>
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
        const u32 n = static_cast<u32>(nums.size());
        int target = 0;
        std::array<u32, 32> target_counters{};
        for (int v : nums)
        {
            target |= v;
            while (v)
            {
                u8 k = std::countr_zero(std::bit_cast<u32>(v)) & 0xFF;
                ++target_counters[k];
                v &= ~(1 << k);
            }
        }

        std::array<u32, 32> counters{};

        u32 i = 0, j = 0;

        int acc = 0;
        while (i != n)
        {
            if (i != j && acc == target)
            {
                int v = nums[i];

                while (v)
                {
                    u8 k = std::countr_zero(std::bit_cast<u32>(v)) & 0xFF;
                    acc &= ~(int{!--counters[k]} << k);
                    target &= ~(int{!--target_counters[k]} << k);
                    v &= ~(1 << k);
                }

                nums[i] = static_cast<int>(j - i);

                ++i;
            }
            else
            {
                int v = nums[j];
                acc |= v;

                while (v)
                {
                    u8 k = std::countr_zero(std::bit_cast<u32>(v)) & 0xFF;
                    ++counters[k];
                    v &= ~(1 << k);
                }

                ++j;
            }
        }

        return std::move(nums);
    }
};
