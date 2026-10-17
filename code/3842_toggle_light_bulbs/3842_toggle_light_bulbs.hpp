#include <vector>

#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "pyramid_bitset/pbs_set.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr auto toggleLightBulbs(
        const std::vector<int>& bulbs) noexcept
    {
        PyramidBitset<128> b{};

        u8 n = 0;
        for (int i : bulbs)
        {
            bool v = pbs_get(b, i & 0xFF);
            pbs_set(b, i & 0xFF, !v);
            n -= v;
            n += !v;
        }

        std::vector<int> r;
        r.reserve(n);
        while (n--)
        {
            auto i = pbs_min(b);
            pbs_remove(b, i);
            r.emplace_back(i);
        }

        return r;
    }
};
