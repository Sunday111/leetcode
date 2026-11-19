
#include <string_view>
#include <unordered_map>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    using Key = u64;
    std::unordered_map<Key, u32> memo;
    std::string_view a, b;
    u32 la, lb;

    [[nodiscard]] u32 dfs(u32 start_a, u32 start_b) noexcept
    {
        if (start_a == la || start_b == lb) return 0;

        auto& r = memo.try_emplace((u64{start_a} << 32) | start_b, 0xFFFFFFFF)
                      .first->second;

        if (r == 0xFFFFFFFF)
        {
            r = 0;

            if (auto b_idx = b.find(a[start_a], start_b); b_idx != b.npos)
            {
                r = 1 + dfs(start_a + 1, cast<u32>(b_idx + 1));
            }

            r = std::max(r, dfs(start_a + 1, start_b));
        }

        return r;
    }

    [[nodiscard]] u32 longestCommonSubsequence(
        std::string_view a_,
        std::string_view b_) noexcept
    {
        a = a_, b = b_;
        la = cast<u32>(a.size()), lb = cast<u32>(b.size());
        return dfs(0, 0);
    }
};
