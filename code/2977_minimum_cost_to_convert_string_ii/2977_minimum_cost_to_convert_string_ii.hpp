#include <algorithm>
#include <array>
#include <bitset>
#include <string>
#include <unordered_map>
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

        // Register unique tokens
        std::unordered_map<std::string_view, u8> token_to_index;
        u8 num_unique_tokens = 0;
        for (std::string_view s : original)
        {
            num_unique_tokens +=
                token_to_index.try_emplace(s, num_unique_tokens).second;
        }
        for (std::string_view s : changed)
        {
            num_unique_tokens +=
                token_to_index.try_emplace(s, num_unique_tokens).second;
        }

        u8 num_sorted = 0;
        std::pair<std::string_view, u8> sorted_tokens[200];

        {
            std::bitset<256> visited;
            for (std::string_view token : original)
            {
                u8 idx = token_to_index[token];
                sorted_tokens[num_sorted] = {token, idx};
                num_sorted += !visited[idx];
                visited[idx] = 1;
            }
            num_sorted = visited.count() & 0xFF;
            std::ranges::sort(
                sorted_tokens,
                sorted_tokens + num_sorted,
                std::less{},
                [&](auto& x)
                {
                    auto [s, i] = x;
                    return std::make_tuple(s.size(), i);
                });
        }

        u32 dist[200][200];  // NOLINT
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            std::fill_n(dist[i], num_unique_tokens, 1000000000);
        }

        assert(num_unique_tokens <= 200);

        // Reset bitsets
        static std::array<PyramidBitset<256>, 200> bitsets{};
        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            bitsets[i].initialize(num_unique_tokens);
        }

        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = token_to_index[original[i]];
            u8 to = token_to_index[changed[i]];
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

        for (u8 i = 0; i != num_unique_tokens; ++i)
        {
            dist[i][i] = 0;
            bitsets[i].add(i);
        }

        static u64 dp[1001];
        const u16 n = cast<u16>(source.size());
        constexpr u64 kHuge = 100'000'000'000'000;
        dp[n] = 0;

        for (u16 i = n - 1; i != 0xFFFF; --i)
        {
            auto& dpi = dp[i] = kHuge;
            if (source[i] == target[i]) dpi = dp[i + 1];

            std::string_view sub_src = source.substr(i);

            u16 max_l = n - i;
            for (u8 j = 0; j != num_sorted; ++j)
            {
                auto& [src_token, src_idx] = sorted_tokens[j];

                u16 l = cast<u16>(src_token.size());
                if (l > max_l) break;
                if (!sub_src.starts_with(src_token)) continue;

                auto tgt_token = target.substr(i, l);
                if (auto it = token_to_index.find(tgt_token);
                    it != token_to_index.end() &&
                    bitsets[src_idx].get(it->second))
                {
                    dpi = std::min(dpi, dist[src_idx][it->second] + dp[i + l]);
                }
            }
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};
