#pragma once

#include <algorithm>
#include <array>
#include <span>
#include <string_view>

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    using i32 = int32_t;
    using u32 = uint32_t;

    [[nodiscard]] static std::span<u16, 150'000> get_static_data() noexcept
    {
        static std::array<u16, 150'000> data;  // NOLINT
        return data;
    }

    [[nodiscard]] static int maxDifference(std::string_view s, u32 k) noexcept
    {
        const u32 n = static_cast<u32>(s.size());

        auto solve_for_pair =
            [&](std::span<const u16> cnt_a, std::span<const u16> cnt_b)
        {
            int cnt = std::numeric_limits<int>::lowest();
            constexpr int INF = 1e8;

            std::array<std::array<int, 2>, 2> parity{{
                {INF, INF},
                {INF, INF},
            }};
            u16 prev_a = 0, prev_b = 0;
            for (u32 l = 0, r = k - 1; r != n; ++r)
            {
                const u16 freq_a = cnt_a[r], freq_b = cnt_b[r];
                while (r + 1 >= k + l && freq_b >= 2 + prev_b)
                {
                    parity[prev_a & 1][prev_b & 1] = std::min(
                        parity[prev_a & 1][prev_b & 1],
                        static_cast<i32>(prev_a) - static_cast<int>(prev_b));
                    prev_a = cnt_a[l], prev_b = cnt_b[l];
                    l++;
                }
                cnt = std::max(
                    cnt,
                    static_cast<i32>(freq_a) - static_cast<i32>(freq_b) -
                        parity[1 - (freq_a & 1)][freq_b & 1]);
            }
            return cnt;
        };

        const auto all_freq = get_static_data().subspan(0, n * 5);
        std::ranges::fill(all_freq, 0);

        std::array<std::span<u16>, 5> freq{};
        for (u32 i = 0; i != 5; ++i)
        {
            freq[i] = std::span{all_freq}.subspan(i * n, n);
        }

        freq[static_cast<u8>(s.front() - '0')].front()++;
        for (u32 i = 1; i != n; ++i)
        {
            for (u8 d = 0; d != 5; d++) freq[d][i] = freq[d][i - 1];
            freq[static_cast<u8>(s[i] - '0')][i]++;
        }

        int ans = std::numeric_limits<int>::min();
        for (u8 a = 0; a != 5; ++a)
        {
            if (!freq[a].back()) continue;

            for (u8 b = 0; b != 5; ++b)
            {
                if (a == b || !freq[b].back()) continue;

                ans = std::max(ans, solve_for_pair(freq[a], freq[b]));
            }
        }

        return ans;
    }
};
