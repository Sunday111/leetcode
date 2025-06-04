#pragma once

#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    static constexpr u16 kMaxN = 20'000;

    [[nodiscard]] static constexpr int candy(std::vector<int>& ratings)
    {
        const u16 n = static_cast<u16>(ratings.size());

        if (n < 2) return n;

        std::array<u16, kMaxN> cnt;  // NOLINT
        std::fill_n(cnt.begin(), n, 1);

        uint32_t result = n;

        // left to right
        u16 i = 0;
        u16 pr = ratings[i] & 0xFFFF, pc = cnt[i];
        while (++i != n)
        {
            u16 ir = ratings[i] & 0xFFFF;
            u16& ic = cnt[i];

            if (ir > pr && ic <= pc)
            {
                u16 add = (pc - ic) + 1;
                result += add;
                ic += add;
            }

            pc = ic, pr = ir;
        }

        // right to left
        --i;
        pr = ratings[i] & 0xFFFF, pc = cnt[i];
        do
        {
            --i;

            u16 ir = ratings[i] & 0xFFFF;
            u16& ic = cnt[i];

            if (ir > pr && ic <= pc)
            {
                u16 add = (pc - ic) + 1;
                result += add;
                ic += add;
            }

            pc = ic, pr = ir;
        } while (i != 0);

        return std::bit_cast<int32_t>(result);
    }
};
