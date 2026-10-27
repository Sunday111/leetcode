#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <ranges>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

    // Columns are indexed from 1.
    inline static u64 dp[1001][16];

    // m[i] selects the lower 2^i bits of each 2^(i+1)-bit group.
    // For example, m[1] = ...0011 0011: the lower 2 bits of each 4-bit
    // group.
    inline static constexpr u64 m[] = {
        0x5555555555555555,
        0x3333333333333333,
        0x0F0F0F0F0F0F0F0F,
        0x00FF00FF00FF00FF,
        0x0000FFFF0000FFFF,
        0x00000000FFFFFFFF,
    };

    [[gnu::no_sanitize_address, gnu::flatten, gnu::target("bmi,bmi2,avx2")]]
    auto minCost(const std::vector<std::vector<int>>& g) const noexcept
    {
        const u32 w = g[0].size() & 1023;

        [[unlikely]] if (g.size() == 1)
        {
            return *std::ranges::fold_left_first(g.front(), std::bit_xor{});
        }

        [[unlikely]] if (g[0].size() == 1)
        {
            return *std::ranges::fold_left_first(
                g | std::views::join,
                std::bit_xor{});
        }

        std::memset(dp, 0, (w + 1) * sizeof(dp[0]));
        int first = 0;
        for (u32 x = 1; x != w + 1; ++x)
        {
            first ^= g[0][x - 1];
            dp[x][first >> 6] = 1ULL << (first & 63);
        }
        first = g[0][0];
        for (u32 y = 1; y != g.size(); ++y)
        {
            auto& row = g[y];
            std::memset(dp[1], 0, sizeof(dp[1]));
            first ^= row[0];
            dp[1][first >> 6] = 1ULL << (first & 63);
            for (u32 x = 2; x != w + 1; ++x)
            {
                u64 t[16];
                for (u32 i = 0; i != 16; ++i)
                {
                    t[i] = dp[x][i] | dp[x - 1][i];
                }
                u32 v = row[x - 1] & 1023;
                // Low XOR bits swap blocks within every word. Unrolling keeps
                // the shifts constant so AVX2 can process four words together.
#pragma clang loop unroll(full)
                for (u32 k = 0; k != 6; ++k)
                {
                    if (!(v & (1u << k))) continue;
                    u32 shift = 1u << k;
                    for (u32 i = 0; i != 16; ++i)
                    {
                        t[i] =
                            ((t[i] & m[k]) << shift) | ((t[i] >> shift) & m[k]);
                    }
                }
                // High XOR bits permute whole words.
                for (u32 i = 0; i != 16; ++i) dp[x][i ^ (v >> 6)] = t[i];
            }
        }

        int wi = 0;
        while (!dp[w][wi]) ++wi;
        return (wi << 6) | __builtin_ctzll(dp[w][wi]);
    }
};

#include "sync_stdio.hpp"
