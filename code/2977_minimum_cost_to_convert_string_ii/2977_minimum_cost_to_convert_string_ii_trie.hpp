#include <algorithm>
#include <array>
#include <bitset>
#include <string>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"

class Solution
{
public:
    i64 minimumCost(
        std::string_view source,
        std::string_view target,
        std::vector<std::string>& original,
        std::vector<std::string>& changed,
        std::vector<int>& cost)
    {
        if (source == target) return 0;

        static std::array<u32, 26> trie_links[200000];
        static u8 trie_ids[200000];
        u32 next_node = 0;
        u8 num_unique_tokens = 0;

        // reset trie
        trie_links[0].fill(~u32{});
        trie_ids[0] = 0xFF;
        num_unique_tokens = 0;
        next_node = 1;

        auto trie_insert = [&](std::string_view s)
        {
            u32 cur = 0;
            for (char c : s)
            {
                u8 char_index = (c - 'a') & 0xFF;
                if (~u32{} == trie_links[cur][char_index])
                {
                    trie_links[cur][char_index] = next_node;
                    trie_links[next_node].fill(~u32{});
                    trie_ids[next_node] = 0xFF;
                    ++next_node;
                }
                cur = trie_links[cur][char_index];
            }
            if (trie_ids[cur] == 0xFF) trie_ids[cur] = num_unique_tokens++;
            return trie_ids[cur];
        };

        u16 max_len = 0;

        // Reset bitsets
        static std::array<PyramidBitset<256>, 200> bitsets{};
        for (u8 i = 0; i != 200; ++i)
        {
            bitsets[i].initialize(200);
        }
        u32 dist[200][200];  // NOLINT
        for (u8 i = 0; i != 200; ++i)
        {
            std::fill_n(dist[i], 200, 1000000000);
        }

        u8 num_sorted = 0;
        std::pair<std::string_view, u8> sorted_tokens[200];
        std::bitset<256> uniq_orig;
        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = trie_insert(original[i]);
            sorted_tokens[num_sorted] = {original[i], from};
            num_sorted += !uniq_orig[from];
            uniq_orig[from] = 1;

            max_len = cast<u16>(std::max<size_t>(max_len, original[i].size()));

            u8 to = trie_insert(changed[i]);
            dist[from][to] = std::min(dist[from][to], cast<u32>(cost[i]));
            bitsets[from].add(to);
        }
        std::ranges::sort(
            sorted_tokens,
            sorted_tokens + num_sorted,
            std::less{},
            [&](auto& x) { return std::get<0>(x).size(); });

        for (u8 k = 0; k != num_unique_tokens; ++k)
        {
            for (u8 i = 0; i != num_unique_tokens; ++i)
            {
                auto& bi = bitsets[i];
                if (!bi.get(k)) continue;

                for (auto bk = bitsets[k]; !bk.is_empty();)
                {
                    u8 j = bk.min();
                    bk.remove(j);
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    bi.add(j);
                }
            }
        }

        static u64 dp[1001];
        const u16 n = cast<u16>(source.size());
        constexpr u64 kHuge = 100'000'000'000'000;
        dp[n] = 0;

        for (u16 i = n - 1; i != 0xFFFF; --i)
        {
            u64 x = dp[i + 1] + (kHuge & -u64{source[i] != target[i]});

            u32 curS = 0, curT = 0;

            const auto ll = std::min<u16>(i + max_len, n);
            for (u16 j = i; j != ll && (curS | curT) != ~u32{}; ++j)
            {
                curS = trie_links[curS][cast<u8>(source[j] - 'a')];
                curT = trie_links[curT][cast<u8>(target[j] - 'a')];

                if ((curS | curT) != ~u32{} &&
                    (trie_ids[curS] | trie_ids[curT]) != 0xFF)
                {
                    auto c = dist[trie_ids[curS]][trie_ids[curT]];
                    if (c < 1000000000)
                    {
                        x = std::min(x, c + dp[j + 1]);
                    }
                }
            }

            dp[i] = std::min(x, kHuge);
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};
