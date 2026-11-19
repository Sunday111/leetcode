#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    static constexpr u16 kMaxN = 20'000;

    [[nodiscard]] static constexpr int candy(std::vector<int>& ratings)
    {
        const u16 n = static_cast<u16>(ratings.size());
        const u16 last_i = n - 1;

        std::array<u16, kMaxN> inices_arr;  // NOLINT
        std::span<u16> indices{inices_arr.begin(), ratings.size()};
        for (u16 i = 0; i != indices.size(); ++i) indices[i] = i;
        std::ranges::sort(
            indices,
            std::less{},
            [&](u16 i) { return ratings[i]; });

        std::array<u16, kMaxN> cnt_arr;  // NOLINT
        std::span<u16> cnt{cnt_arr.begin(), ratings.size()};
        std::ranges::fill(cnt, 1);

        uint32_t result = n;
        for (u16 i : indices)
        {
            u16 ir = ratings[i] & 0xFFFF;
            u16& ic = cnt[i];
            if (i != 0)
            {
                u16 l = i - 1;
                u16 lr = ratings[l] & 0xFFFF;
                u16& lc = cnt[l];
                if (ir > lr && ic <= lc)
                {
                    u16 add = (lc - ic) + 1;
                    result += add;
                    ic += add;
                }
            }
            if (i != last_i)
            {
                u16 r = i + 1;
                u16 rr = ratings[r] & 0xFFFF;
                u16& rc = cnt[r];
                if (ir > rr && ic <= rc)
                {
                    u16 add = (rc - ic) + 1;
                    result += add;
                    ic += add;
                }
            }
        }

        return std::bit_cast<int32_t>(result);
    }
};
