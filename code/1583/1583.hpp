#pragma once

#include <array>
#include <bitset>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    u16 unhappyFriends(
        int n,
        const std::vector<std::vector<int>>& preferences,
        const std::vector<std::vector<int>>& in_pairs)
    {
        u16 r = 0;
        std::array<u16, 500> pairs;  // NOLINT
        std::array<std::bitset<500>, 500> variants;

        for (const auto& pair : in_pairs)
        {
            const u16 x = pair[0] & 0xFFFF, y = pair[1] & 0xFFFF;
            pairs[x] = y;
            pairs[y] = x;
        }

        for (u16 x = 0; x != n; ++x)
        {
            const u16 y = pairs[x];
            for (auto preference : preferences[x])
            {
                if (preference == y) break;
                // x would prefer "preference" over y
                variants[preference & 0xFFFF][x] = true;
            }
        }

        for (u16 x = 0; x != n; ++x)
        {
            const u16 y = pairs[x];
            auto& x_variants = variants[x];
            for (auto preference : preferences[x])
            {
                if (preference == y) break;
                if (x_variants[preference & 0xFFFF])
                {
                    ++r;
                    break;
                }
            }
        }

        return r;
    }
};
