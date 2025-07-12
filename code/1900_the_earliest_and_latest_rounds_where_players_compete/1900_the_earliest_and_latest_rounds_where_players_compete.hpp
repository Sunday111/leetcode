#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

class Solution
{
    [[nodiscard]] static constexpr u16 reverse(u16 x) noexcept
    {
        x = (((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1)) & 0xFFFF;
        x = (((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2)) & 0xFFFF;
        x = (((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4)) & 0xFFFF;
        x = (((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8)) & 0xFFFF;
        return x;
    }

    [[nodiscard]] static constexpr u16 reverse_inverse_k_lsb(
        u16 x,
        u8 k) noexcept
    {
        u16 r = reverse(x);
        u16 ir = (~r) & 0xFFFF;
        u16 irk = ir >> (16 - k);
        return irk;
    }

    struct Query
    {
        u16 n : 5;
        u16 a : 5;
        u16 b : 6;
    };

    struct Result
    {
        u16 min : 8;
        u16 max : 7;
        u16 initialized : 1;
    };

    inline static auto memo = []  // NOLINT
    {
        std::array<Result, (1 << 16)> memo;  // NOLINT
        std::ranges::fill(memo, Result{.min = 255, .max = 0, .initialized = 0});
        for (u8 n = 2; n != 29; ++n)
        {
            u8 h = n / 2;
            for (u8 i = 0; i != h; ++i)
            {
                memo[std::bit_cast<u16>(Query{
                    .n = n,
                    .a = i,
                    .b = static_cast<u8>(n - (i + 1)),
                })] = {1, 1, 1};
            }
        }

        return memo;
    }();

    template <u8 n>
    [[nodiscard]] static const Result& dfs(u8 a, u8 b) noexcept
    {
        constexpr u8 h = n / 2;
        constexpr u8 num_winners = h + (n & 1);
        constexpr u16 e = (1u << h) & 0xFFFF;
        constexpr u16 mid_mask = e * (n & 1);
        auto& r = memo[std::bit_cast<u16>(Query{.n = n, .a = a, .b = b})];
        if (!r.initialized)
        {
            r.initialized = true;
            const u32 a_mask = ~(0xFFFFFFFF << a), b_mask = ~(0xFFFFFFFF << b);
            for (u16 w = 0; w != e; ++w)
            {
                const u32 winners =
                    (u32{reverse_inverse_k_lsb(w, h)} << num_winners) |
                    mid_mask | w;
                if ((winners & (1 << a)) && (winners & (1 << b)))
                {
                    u8 num_winners_before_a =
                        std::popcount(winners & a_mask) & 0xFF;
                    u8 num_winners_before_b =
                        std::popcount(winners & b_mask) & 0xFF;
                    const auto& recursive = dfs<num_winners>(
                        num_winners_before_a,
                        num_winners_before_b);
                    r.min = std::min<u8>(r.min, recursive.min + 1);
                    r.max = std::max<u8>(r.max, recursive.max + 1);
                }
            }
        }

        return r;
    }

public:
    static constexpr std::array kSolutionN{
        &dfs<2>,  &dfs<3>,  &dfs<4>,  &dfs<5>,  &dfs<6>,  &dfs<7>,  &dfs<8>,
        &dfs<9>,  &dfs<10>, &dfs<11>, &dfs<12>, &dfs<13>, &dfs<14>, &dfs<15>,
        &dfs<16>, &dfs<17>, &dfs<18>, &dfs<19>, &dfs<20>, &dfs<21>, &dfs<22>,
        &dfs<23>, &dfs<24>, &dfs<25>, &dfs<26>, &dfs<27>, &dfs<28>,
    };

    [[nodiscard]] static std::vector<int>
    earliestAndLatest(u8 n, u8 a, u8 b) noexcept
    {
        const auto& r = kSolutionN[n - 2](a - 1, b - 1);
        return {r.min, r.max};
    }
};
