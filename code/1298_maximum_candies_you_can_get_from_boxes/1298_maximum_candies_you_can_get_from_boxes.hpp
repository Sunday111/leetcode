#pragma once

#include <bitset>
#include <cassert>
#include <vector>

class Solution
{
public:
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;

    static constexpr u16 kMaxN = 1000;

    [[nodiscard]] static constexpr u32 maxCandies(
        std::vector<int>& is_open,
        std::vector<int>& candies,
        const std::vector<std::vector<int>>& keys,
        const std::vector<std::vector<int>>& containedBoxes,
        std::vector<int>& initialBoxes) noexcept
    {
        std::bitset<kMaxN> closed_boxes;
        std::array<u16, kMaxN> q;  // NOLINT
        u16 qfront = 0, qback = 0;

        for (int ibox : initialBoxes)
        {
            u16 box = static_cast<u16>(ibox);
            if (is_open[box])
            {
                q[qback++] = box;
            }
            else
            {
                closed_boxes[box] = true;
            }
        }

        u32 num_candies = 0;

        while (qfront != qback)
        {
            const u16 box = q[qfront++];
            num_candies += static_cast<u32>(candies[box]);
            for (int ikey : keys[box])
            {
                u16 key = static_cast<u16>(ikey);
                is_open[key] = true;

                if (closed_boxes[key])
                {
                    closed_boxes[key] = false;
                    q[qback++] = key;
                }
            }

            for (int ibox : containedBoxes[box])
            {
                u16 contained_box = static_cast<u16>(ibox);
                if (is_open[contained_box])
                {
                    q[qback++] = contained_box;
                }
                else
                {
                    closed_boxes[contained_box] = true;
                }
            }
        }

        return num_candies;
    }
};
