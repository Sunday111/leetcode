#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    const char *src{}, *dst{};
    u16 ls{}, ld{};

    inline static u16 memo[500][500];

    u16 dfs(u16 is, u16 id)
    {
        // if there is nothing left to consider in dst or src
        // complete aother one with insertions or deletions
        if (u16 rem_src = ls - is, rem_dst = ld - id; !rem_src || !rem_dst)
        {
            return rem_src | rem_dst;
        }

        u16& r = memo[is][id];
        if (r == 0xFFFF)
        {
            // consider insertion
            r = dfs(is, id + 1) + 1;

            // consider replacement
            r = std::min<u16>(r, dfs(is + 1, id + 1) + (src[is] != dst[id]));

            // consider deletion
            r = std::min<u16>(r, dfs(is + 1, id) + 1);
        }
        return r;
    }

    [[nodiscard]] int minDistance(
        std::string_view word1,
        std::string_view word2) noexcept
    {
        src = word1.data(), dst = word2.data();
        ls = word1.size() & 0xFFFF, ld = word2.size() & 0xFFFF;
        for (u16 i = 0; i != ls; ++i) std::fill_n(memo[i], ld, 0xFFFF);
        return dfs(0, 0);
    }
};
