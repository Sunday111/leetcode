#include <array>
#include <bit>
#include <cstdint>
#include <string>




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

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
