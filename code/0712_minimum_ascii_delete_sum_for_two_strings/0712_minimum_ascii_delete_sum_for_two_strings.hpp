#include <string_view>

#include "int_if.hpp"
#include "no_sanitizers.hpp"

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr int minimumDeleteSum(
        std::string_view va,
        std::string_view vb) noexcept NO_SANITIZERS
    {
        int curr[1001];
        const u16 la = va.size() & 0xFFFF, lb = vb.size() & 0xFFFF;

        curr[0] = 0;
        for (u16 j = 0; j != lb; ++j) curr[j + 1] = curr[j] + vb[j];

        for (u16 i = 0; i != la; ++i)
        {
            char a = va[i];
            int e = curr[0];
            curr[0] += a;

            for (u16 j = 0; j != lb;)
            {
                char b = vb[j];
                int pj = curr[j];
                ++j;
                curr[j] =
                    iif(a == b,
                        std::exchange(e, curr[j]),
                        std::min(curr[j] + a, pj + b));
            }
        }

        return curr[lb];
    }
};

#include "sync_stdio.hpp"
