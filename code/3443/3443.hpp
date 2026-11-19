#pragma once

#include <array>
#include <cstdlib>
#include <string_view>

using u8 = uint8_t;
using u32 = uint32_t;
using i32 = int32_t;

struct Vec2
{
    i32 x, y;
};

class Solution
{
public:
    [[nodiscard]] static constexpr u8 charToId(char c) noexcept
    {
        return std::bit_cast<u8>(c) / 4u - 17u;
    }
    static constexpr std::array<Vec2, 5> kOffsets{{
        {1, 0},
        {0, 0},
        {0, 1},
        {0, -1},
        {-1, 0},
    }};

    [[nodiscard]] static constexpr u32 maxDistance(
        std::string_view s,
        u32 k) noexcept
    {
        constexpr u8 kEastCID = charToId('E');
        constexpr u8 kWestCID = charToId('W');
        constexpr u8 kNorthCID = charToId('N');
        constexpr u8 kSouthCID = charToId('S');

        const u32 n = static_cast<u32>(s.size());

        u32 r = 0;
        Vec2 p{0, 0};
        std::array<u32, 5> cnt{};
        u32 tail = n - 1;
        for (u32 i = 0; i != n; ++i, --tail)
        {
            const char c = s[i];
            u8 cid = charToId(c);
            ++cnt[cid];
            p.x += kOffsets[cid].x;
            p.y += kOffsets[cid].y;

            u32 hLow = std::min(cnt[kEastCID], cnt[kWestCID]);
            u32 vLow = std::min(cnt[kSouthCID], cnt[kNorthCID]);
            u32 u = std::min(hLow + vLow, k);
            const u32 dist = static_cast<u32>(std::abs(p.x) + std::abs(p.y));
            const u32 possible_md = dist + 2 * u + std::min(tail, k - u);
            if (possible_md > r) r = possible_md;
        }

        return r;
    }
};
