#include <string>
#include <vector>

#include "bit_manipultaion/clear_bit.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    constexpr auto partitionLabels(const std::string& s) noexcept
    {
        u32 lb = 0, rb = 0;
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

            rb = clear_bit(rb, i, !--freq[i]);
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
