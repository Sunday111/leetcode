#include <string>
#include <vector>

#include "bitsets/bitset_view/bsv_set_if.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    static constexpr auto partitionLabels(const std::string& s) noexcept
    {
        u32 lb = 0, rb = 0;
        const BitsetView<u32, 26> remaining{&rb};
        u16 n = 0, freq[26]{};
        std::vector<int> r;

        for (char c : s)
        {
            u8 i = (c - 'a') & 31;
            rb |= (1u << i);
            ++freq[i];
        }

        for (char c : s)
        {
            u8 i = (c - 'a') & 31;

            bsv_set_if<false>(remaining, i, !--freq[i]);
            lb |= (1u << i);
            ++n;

            if (lb & rb) continue;
            r.emplace_back(n);
            lb = 0;
            n = 0;
        }

        return r;
    }
};
