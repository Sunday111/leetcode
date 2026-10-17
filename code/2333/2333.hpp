#include <array>
#include <bit>
#include <cstdlib>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_is_empty.hpp"
#include "pyramid_bitset/pbs_max.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "sync_stdio.hpp"

class Solution
{
    static constexpr u32 kMaxDiff = 100000;
    static constexpr u32 kNumBlocks = (kMaxDiff + 64) / 64;
    inline static std::array<u32, kMaxDiff + 1> frequency{};
    inline static std::array<u64, kNumBlocks> occupied_values{};
    inline static PyramidBitset<kNumBlocks> occupied_blocks{};

public:
    u64 minSumSquareDiff(
        const std::vector<int>& nums1,
        const std::vector<int>& nums2,
        u32 k1,
        u32 k2)
    {
        occupied_values[0] = 1;
        pbs_add(occupied_blocks, 0);
        for (size_t i = 0; i < nums1.size(); ++i)
        {
            u32 diff = static_cast<u32>(std::abs(nums1[i] - nums2[i]));
            if (frequency[diff]++ == 0)
            {
                u32 block = diff >> 6;
                if (!occupied_values[block])
                {
                    pbs_add(occupied_blocks, static_cast<u16>(block));
                }
                occupied_values[block] |= u64{1} << (diff & 63);
            }
        }

        u32 block = 0;
        u64 bits = 0;
        auto pop_max = [&] [[gnu::always_inline]]
        {
            if (!bits)
            {
                block = pbs_max(occupied_blocks);
                pbs_remove(occupied_blocks, static_cast<u16>(block));
                bits = std::exchange(occupied_values[block], 0);
            }
            u32 bit = 63 - static_cast<u32>(std::countl_zero(bits));
            bits ^= u64{1} << bit;
            return block * 64 + bit;
        };

        u32 k = k1 + k2, level = pop_max();
        u64 count = std::exchange(frequency[level], 0), sum{};
        while (level)
        {
            u32 next = pop_max();
            u64 next_count = std::exchange(frequency[next], 0);
            u64 cost = (level - next) * count;
            if (k < cost)
            {
                sum = u64{next} * next * next_count;
                break;
            }

            k -= static_cast<u32>(cost);
            level = next;
            count += next_count;
        }

        if (level)
        {
            sum += count * level * level + k / count * (k + k % count) +
                   k % count - 2 * u64{level} * k;
        }

        while (bits || !pbs_is_empty(occupied_blocks))
        {
            u32 diff = pop_max();
            sum += u64{diff} * diff * std::exchange(frequency[diff], 0);
        }
        return sum;
    }
};
