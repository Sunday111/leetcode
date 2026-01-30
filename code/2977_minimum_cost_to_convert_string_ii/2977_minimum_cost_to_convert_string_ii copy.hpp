#include <algorithm>
#include <array>
#include <bitset>
#include <string>
#include <unordered_map>
#include <vector>

#include "bump_hash_map.hpp"
#include "cast.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"

using SolutionStorage = GlobalBufferStorage<1u << 16>;

struct TrieNode
{
    std::array<TrieNode*, 26> links;
    i16 id;
};

static constexpr int N = 200000;  // 200 (strings)*1000 (length)
inline static TrieNode POOL[N];   // NOLINT
inline static u32 next_node = 0;  // NOLINT
inline static u16 trie_idx = 0;   // NOLINT

struct Trie
{
    TrieNode* root;
    TrieNode* newNode()
    {
        TrieNode* node = &POOL[next_node++];
        node->links.fill(nullptr);
        node->id = -1;
        return node;
    }
    void reset()
    {
        next_node = trie_idx = 0;
        root = newNode();
    }

    int insert(std::string_view s)
    {  // returning id
        TrieNode* cur = root;
        for (char c : s)
        {
            u8 i = (c - 'a') & 0xFF;
            if (!cur->links[i]) cur->links[i] = newNode();
            cur = cur->links[i];
        }
        if (cur->id == -1) cur->id = static_cast<i16>(trie_idx++);
        return cur->id;
    }
};

class Solution
{
public:
    Trie trie;
    i64 minimumCost(
        std::string_view source,
        std::string_view target,
        std::vector<std::string>& original,
        std::vector<std::string>& changed,
        std::vector<int>& cost)
    {
        if (source == target) return 0;

        trie.reset();

        auto arena = SolutionStorage::Instance().StartArena();

        // Register unique tokens
        ObjectWithoutDtor<BumpHashMap<std::string_view, u8, SolutionStorage>>
            token_to_index;
        token_to_index->reserve(400);

        u8 num_unique_tokens = 0;
        for (std::string_view s : original)
        {
            num_unique_tokens +=
                token_to_index->try_emplace(s, num_unique_tokens).second;
        }
        for (std::string_view s : changed)
        {
            num_unique_tokens +=
                token_to_index->try_emplace(s, num_unique_tokens).second;
        }

        u8 num_sorted = 0;
        std::pair<std::string_view, u8> sorted_tokens[200];
        for (std::bitset<256> visited; std::string_view token : original)
        {
            u8 idx = token_to_index.get()[token];
            sorted_tokens[num_sorted] = {token, idx};
            num_sorted += !visited[idx];
            visited[idx] = 1;
        }
        std::ranges::sort(
            sorted_tokens,
            sorted_tokens + num_sorted,
            std::less{},
            [&](auto& x) { return std::get<0>(x).size(); });

        u32 dist[200][200];  // NOLINT
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            std::fill_n(dist[i], num_unique_tokens, 1000000000);
        }

        // Reset bitsets
        static std::array<PyramidBitset<256>, 200> bitsets{};
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            bitsets[i].initialize(num_unique_tokens);
        }

        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = token_to_index.get()[original[i]];
            u8 to = token_to_index.get()[changed[i]];
            dist[from][to] = std::min(dist[from][to], cast<u32>(cost[i]));
            bitsets[from].add(to);
        }

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
            std::string_view sub_src = source.substr(i),
                             sub_tgt = target.substr(i);

            u64 x = dp[i + 1] + (kHuge & -u64{source[i] != target[i]});

            u16 max_l = n - i;
            for (u8 j = 0; j != num_sorted; ++j)
            {
                auto& [src_token, src_idx] = sorted_tokens[j];

                u16 l = cast<u16>(src_token.size());
                if (l > max_l) break;
                if (!sub_src.starts_with(src_token)) continue;

                auto it = token_to_index->find(sub_tgt.substr(0, l));
                if (it != token_to_index->end())
                {
                    u8 tgt_idx = it->second;
                    if (bitsets[src_idx].get(tgt_idx))
                    {
                        x = std::min(x, dist[src_idx][tgt_idx] + dp[i + l]);
                    }
                }
            }

            dp[i] = std::min(x, kHuge);
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};
