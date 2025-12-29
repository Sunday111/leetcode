#include <bitset>
#include <string>
#include <vector>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] FORCE_INLINE static u32 encode(const std::string& s) noexcept
    {
        u32 ans = 0;
        for (char c : s) ans = ans * 7 + ((c - 'A') & 0xFF);
        return ans;
    }

    [[nodiscard]] static bool pyramidTransition(
        std::string& bottom,
        std::vector<std::string>& allowed) noexcept
    {
        u8 pattern[36];
        std::fill_n(pattern, 36, 0);

        for (const auto& s : allowed)
        {
            u8 idx = ((s[0] - 'A') & 0xFF) * 6 + ((s[1] - 'A') & 0xFF);
            pattern[idx] |= 1 << (s[2] - 'A');
        }

        constexpr u32 N = 117649;
        static std::bitset<N> visited[7];
        for (u32 i = 1; i != 7; ++i) visited[i].reset();

        auto test = [&](const std::string& cur, u32 sz)
        {
            for (u32 i = 0; i < sz - 1; i++)
            {
                if (cur[i] == 'G' || !pattern
                                         [((cur[i] - 'A') & 0xFF) * 6 +
                                          ((cur[i + 1] - 'A') & 0xFF)])
                {
                    return false;
                }
            }
            return true;
        };

        std::string next(bottom.size() - 1, 'G');

        auto dfs = [&](auto& dfs,
                       const std::string& cur,
                       std::string& next,
                       u32 i,
                       u32 sz) -> bool
        {
            if (i == sz - 1)
            {
                if (sz == 2) return 1;
                // pruning check
                if (!test(next, sz - 1)) return 0;
                u32 idx = encode(next);
                if (visited[sz - 1][idx]) return 0;

                std::string up(sz - 1, 'G');
                if (!dfs(dfs, next, up, 0, sz - 1))
                {
                    visited[sz - 1][idx] = 1;
                    return 0;
                }
                return true;
            }

            for (u32 mask = pattern[(cur[i] - 'A') * 6 + (cur[i + 1] - 'A')];
                 mask;)
            {
                u8 c = std::countr_zero(mask) & 0xFF;
                mask &= ~(1u << c);
                next[i] = static_cast<char>('A' + c);

                if (dfs(dfs, cur, next, i + 1, sz)) return true;
            }
            return false;
        };

        return dfs(dfs, bottom, next, 0, bottom.size() & 0xFF);
    }
};
