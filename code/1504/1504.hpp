#pragma once

#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    using u32 = uint32_t;
    static u32 numSubmat(std::vector<std::vector<int>>& mat)
    {
        constexpr u16 kEmpty = static_cast<u16>(-1);
        static std::array<u16, 2 << 16> stack;
        stack[kEmpty] = kEmpty;
        u16 top = kEmpty;
        static std::array<u16, 2 << 16> cnt;
        cnt[kEmpty] = 0;

        const u16 r = mat.size() & 0xFFFF, c = mat[0].size() & 0xFFFF;

        u32 ans = 0;
        for (u16 i = 0; i != r; ++i)
        {
            auto& h = mat[i];
            top = kEmpty;
            std::fill_n(cnt.begin(), c, 0);
            for (u16 j = 0; j != c; ++j)
            {
                if (i && h[j]) h[j] += mat[i - 1][j];
                const u16 hj = h[j] & 0xFFFF;
                while (top != kEmpty && h[stack[top]] > hj) --top;
                cnt[j] = ((cnt[stack[top]]) + (hj * (j - stack[top]))) & 0xFFFF;
                ans += cnt[j];
                stack[++top] = j;
            }
        }
        return ans;
    }
};
