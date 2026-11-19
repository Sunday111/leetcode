#include <algorithm>
#include <bitset>
#include <ranges>
#include <span>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "bump_hash_set.hpp"

// 1 <= words.length <= 10^4
// 1 <= words[i].length <= 30

class Solution
{
public:
    using SolutionStorage = GlobalBufferStorage<1 << 20>;
    using Group =
        ObjectWithoutDtor<BumpHashSet<std::string_view, SolutionStorage>>;

    using u16 = uint16_t;
    [[nodiscard]] static constexpr bool wordBreak(
        std::string_view s,
        std::span<Group> groups) noexcept
    {
        std::bitset<32> dp;
        dp[0] = true;

        const u16 n = s.size() & 0xFFFF;

        for (u16 i = 0; i != n && !dp[n]; ++i)
        {
            if (!dp[i]) continue;

            for (auto& group : groups)
            {
                u16 word_length = group->begin()->size() & 0xFFFF;
                if (word_length >= n) break;

                u16 j = i + word_length;
                if (j > n) continue;
                if (dp[j]) continue;

                dp[j] = group->contains(s.substr(i, word_length));
            }
        }

        return dp[n];
    }

    std::vector<std::string> findAllConcatenatedWordsInADict(
        std::vector<std::string>& words)
    {
        auto arena = SolutionStorage::Instance().StartArena();

        std::ranges::sort(words, std::less{}, std::ranges::size);

        std::array<Group, 31> groups_buf;
        std::span<Group> groups;
        {
            u16 num_groups = 1;
            u16 curr_size = words[0].size() & 0xFFFF;
            u16 begin = 0;

            auto close_group = [&](u16 end)
            {
                auto& g = groups_buf[num_groups - 1];
                g->reserve((end - begin) * 2);
                for (u16 i = begin; i != end; ++i) g->emplace(words[i]);
            };

            for (u16 i = 1; i != words.size(); ++i)
            {
                if (u16 s = words[i].size() & 0xFFFF; s != curr_size)
                {
                    close_group(i);
                    ++num_groups;
                    begin = i;
                    curr_size = s;
                }
            }
            close_group(words.size() & 0xFFFF);
            groups = std::span{groups_buf}.first(num_groups);
            groups = std::span{groups_buf}.first(num_groups);
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
