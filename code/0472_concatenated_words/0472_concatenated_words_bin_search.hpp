#include <algorithm>
#include <bitset>
#include <ranges>
#include <span>
#include <string_view>
#include <vector>

// 1 <= words.length <= 10^4
// 1 <= words[i].length <= 30

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr bool wordBreak(
        std::string_view s,
        std::span<std::span<std::string>> groups) noexcept
    {
        std::bitset<32> dp;
        dp[0] = true;

        const u16 n = s.size() & 0xFFFF;

        for (u16 i = 0; i != n && !dp[n]; ++i)
        {
            if (!dp[i]) continue;

            for (auto group : groups)
            {
                u16 word_length = group[0].size() & 0xFFFF;
                if (word_length >= n) break;

                u16 j = i + word_length;
                if (j > n) continue;
                if (dp[j]) continue;

                dp[j] =
                    std::ranges::binary_search(group, s.substr(i, word_length));
            }
        }

        return dp[n];
    }

    std::vector<std::string> findAllConcatenatedWordsInADict(
        std::vector<std::string>& words)
    {
        std::ranges::sort(words, std::less{}, std::ranges::size);

        std::array<std::span<std::string>, 31> groups_buf;
        std::span<std::span<std::string>> groups;
        {
            u16 num_groups = 1;
            u16 curr_size = words[0].size() & 0xFFFF;
            u16 begin = 0;

            for (u16 i = 1; i != words.size(); ++i)
            {
                if (u16 s = words[i].size() & 0xFFFF; s != curr_size)
                {
                    groups_buf[num_groups - 1] =
                        std::span{words}.subspan(begin, i - begin);
                    ++num_groups;
                    begin = i;
                    curr_size = s;
                }
            }
            groups_buf[num_groups - 1] = std::span{words}.subspan(begin);
            groups = std::span{groups_buf}.first(num_groups);
            std::ranges::for_each(groups, std::ranges::sort);
        }

        std::bitset<10048> b;
        for (u16 i = 0; i != words.size(); ++i)
        {
            if (wordBreak(words[i], groups))
            {
                b[i] = true;
            }
        }

        u16 o = 0;
        for (u16 i = 0; i != words.size(); ++i)
        {
            if (b[i])
            {
                words[o++] = std::move(words[i]);
            }
        }

        words.resize(o);
        return std::move(words);
    }
};
