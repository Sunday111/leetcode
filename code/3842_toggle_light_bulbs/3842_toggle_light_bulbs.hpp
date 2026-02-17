#include <vector>

#include "pyramid_bitset.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr auto toggleLightBulbs(
        const std::vector<int>& bulbs) noexcept
    {
        PyramidBitset<128> b;

        u8 n = 0;
        for (int i : bulbs)
        {
            bool v = b.get(i & 0xFF);
            b.set(i & 0xFF, !v);
            n -= v;
            n += !v;
        }

        std::vector<int> r;
        r.reserve(n);
        while (n--)
        {
            auto i = b.min();
            b.remove(i);
            r.emplace_back(i);
        }

        return r;
    }
};
