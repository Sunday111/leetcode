#include <bit>
#include <string>
#include <vector>

#include "force_inline.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"

struct State
{
    u32 chars = 0;
    u16 partitions = 0;

    FORCE_INLINE constexpr void add_char(char c, u8 k) noexcept
    {
        u32 m = 1u << ((c - 'a') & 0x1F);
        u32 new_chars = chars | m;
        bool b = std::popcount(new_chars) > k;
        partitions += b;
        chars = iif(b, m, new_chars);
    }
};

class Solution
{
public:
    static u32 maxPartitionsAfterOperations(const std::string& s, u8 k)
    {
        const u32 n = static_cast<u32>(s.size());
        std::vector<State> pref(n), suff(n);

        State state{};
        for (u32 i = 0; i != n - 1; ++i)
        {
            state.add_char(s[i], k);
            pref[i + 1] = state;
        }

        state = {};
        for (u32 i = n - 1; i != 0; --i)
        {
            state.add_char(s[i], k);
            suff[i - 1] = state;
        }

        u32 r = 0;
        for (u32 i = 0; i != n; ++i)
        {
            auto& [l_chars, l_partitions] = pref[i];
            auto& [r_chars, r_partitions] = suff[i];
            u16 paritions = (l_partitions + r_partitions + 1u) & 0xFFFF;
            u32 lr_num_chars =
                static_cast<u32>(std::popcount(l_chars | r_chars));
            u32 add = (std::min(lr_num_chars + 1u, 26u) <= k)
                          ? 0
                          : ((std::popcount(l_chars) == k &&
                              std::popcount(r_chars) == k && lr_num_chars < 26)
                                 ? 2
                                 : 1);
            r = std::max(r, paritions + add);
        }
        return r;
    }
};
