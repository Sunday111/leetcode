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
    struct StrSearch
    {
        std::string_view s;
        const std::pair<std::string_view, u8>* sorted;
        u16 begin = 0, end = 0;

        [[nodiscard]] FORCE_INLINE constexpr bool update(u16 l) noexcept
        {
            if (l > s.size())
            {
                begin = end;
                return false;
            }

            u16 i = l - 1;
            char c = s[i];
            while (begin != end)
            {
                auto& [tok, idx] = sorted[begin];
                if (i >= tok.size())
                {
                    ++begin;
                    continue;
                }

                if (tok[i] < c)
                {
                    ++begin;
                    continue;
                }

                if (tok[i] == c) break;
                end = begin;
            }

            while (begin != end)
            {
                auto& [tok, idx] = sorted[end - 1];
                if (i >= tok.size())
                {
                    --end;
                    continue;
                }

                if (tok[i] > c)
                {
                    --end;
                    continue;
                }

                break;
            }

            return begin != end;
        }
    };

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

        u8 nums_src_tokens = 0;
        std::pair<std::string_view, u8> src_tokens[200];

        {
            std::bitset<256> visited;
            for (std::string_view token : original)
            {
                u8 idx = token_to_index[token];
                src_tokens[nums_src_tokens] = {token, idx};
                nums_src_tokens += !visited[idx];
                visited[idx] = 1;
            }
            nums_src_tokens = visited.count() & 0xFF;
            std::ranges::sort(
                src_tokens,
                src_tokens + nums_src_tokens,
                std::less{});
        }

        u8 num_tgt_tokens = 0;
        std::pair<std::string_view, u8> tgt_tokens[200];

        {
            std::bitset<256> visited;
            for (std::string_view token : changed)
            {
                u8 idx = token_to_index[token];
                tgt_tokens[num_tgt_tokens] = {token, idx};
                num_tgt_tokens += !visited[idx];
                visited[idx] = 1;
            }
            num_tgt_tokens = visited.count() & 0xFF;
            std::ranges::sort(
                tgt_tokens,
                tgt_tokens + num_tgt_tokens,
                std::less{});
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

        static u64 dp[1001];
        const u16 n = cast<u16>(source.size());
        constexpr u64 kHuge = 100'000'000'000'000;
        dp[n] = 0;

        for (u16 i = n - 1; i != 0xFFFF; --i)
        {
            u64 x = dp[i + 1] + (kHuge & -u64{source[i] != target[i]});

            StrSearch src_search{
                .s = source.substr(i),
                .sorted = src_tokens,
                .begin = 0,
                .end = nums_src_tokens};
            StrSearch tgt_search{
                .s = target.substr(i),
                .sorted = tgt_tokens,
                .begin = 0,
                .end = num_tgt_tokens};

            for (u16 l = 1; src_search.update(l) && tgt_search.update(l); ++l)
            {
                auto& [src_tok, src_idx] = src_search.sorted[src_search.begin];
                auto& [tgt_tok, tgt_idx] = tgt_search.sorted[tgt_search.begin];
                if (src_tok.size() != l || tgt_tok.size() != l) continue;
                if (!bitsets[src_idx].get(tgt_idx)) continue;
                x = std::min(x, dist[src_idx][tgt_idx] + dp[i + l]);
            }
            dp[i] = std::min(x, kHuge);
        }

        if (dp[0] >= kHuge) return -1;
        return cast<i64>(dp[0]);
    }
};
