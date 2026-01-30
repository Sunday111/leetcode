#include <array>
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

        std::array<std::array<u32, 256>, 256> dist;  // NOLINT
        for (auto& x : dist) x.fill(1000000000);

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

        assert(num_unique_tokens <= 200);

        // Reset bitsets
        static std::array<PyramidBitset<256>, 256> bitsets{};
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
            std::string_view sub_tgt = target.substr(i);

            for (auto& [src_token, src_idx] : token_to_index)
            {
                if (!sub_src.starts_with(src_token)) continue;

                const u16 l = cast<u16>(src_token.size());
                auto tgt_token = sub_tgt.substr(0, l);
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
