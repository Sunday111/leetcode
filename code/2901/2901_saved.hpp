#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <vector>

class Solution2
{
public:
    [[nodiscard]] constexpr std::vector<std::string>
    getWordsInLongestSubsequence(
        std::vector<std::string>& words,
        std::vector<int>& groups)
    {
        using DpIndex = uint16_t;
        const DpIndex n = static_cast<DpIndex>(words.size());
        constexpr DpIndex kInvalidDpIndex = 1000;

        struct DpEntry
        {
            DpIndex prev_idx = kInvalidDpIndex;
            DpIndex len = 0;
        };

        std::array<DpEntry, 1000> dp{};

        DpIndex longest_dist = 0;
        DpIndex longest_dist_last_index = 0;

        auto bad_distance = [](const std::string& a, const std::string& b)
        {
            auto n = static_cast<uint8_t>(a.size());
            uint8_t distance = 0;
            for (uint8_t i = 0; i != n; ++i)
            {
                if (a[i] != b[i])
                {
                    if (++distance > 1)
                    {
                        return true;
                    }
                }
            }

            return distance != 1;
        };

        for (DpIndex i = 0; i != n; ++i)
        {
            const int gi = groups[i];
            const auto& wi = words[i];
            const auto& dpi = dp[i];

            for (DpIndex j = i + 1; j != n; ++j)
            {
                if (const int gj = groups[j]; gi == gj)
                {
                    continue;
                }

                const auto& wj = words[j];
                if (wi.size() != wj.size())
                {
                    continue;
                }

                auto& dpj = dp[j];
                if (dpi.len < dpj.len)
                {
                    continue;
                }

                if (bad_distance(wi, wj))
                {
                    continue;
                }

                dpj.len = dpi.len + 1;
                dpj.prev_idx = i;

                if (dpj.len > longest_dist)
                {
                    longest_dist = dpj.len;
                    longest_dist_last_index = j;
                }
            }
        }

        std::vector<std::string> r;
        r.reserve(longest_dist + 1);
        do
        {
            r.emplace_back(std::move(words[longest_dist_last_index]));
            longest_dist_last_index = dp[longest_dist_last_index].prev_idx;
        } while (longest_dist_last_index != kInvalidDpIndex);

        std::ranges::reverse(r);

        return r;
    }
};
