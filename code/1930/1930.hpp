#include <array>
#include <bit>
#include <string>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u16 countPalindromicSubsequence(
        const std::string& s) noexcept
    {
        std::array<u32, 26> right{}, r{};
        u32 lbs = 0, rbs = 0, n = s.size() & 0xFFFFFFFF;

        for (char c : s)
        {
            u8 ci = (c - 'a') & 0xFF;
            ++right[ci];
            rbs |= (1u << ci);
        }

        // max possible result is 26^2 so 16 bit is enough
        u16 ans = 0;
        u32 lim = std::popcount(rbs) & 0xFF;
        lim *= lim;

        for (u32 i = 0; i != n && ans != lim; ++i)
        {
            u8 ci = (s[i] - 'a') & 0xFF;
            rbs &= ~(u32{!--right[ci]} << ci);
            u32 x = (lbs & rbs);
            ans += std::popcount(x & u32{~r[ci]}) & 0xFF;
            r[ci] |= x;
            lbs |= (1u << ci);
        }

        return ans;
    }
};

#include "sync_stdio.hpp"
