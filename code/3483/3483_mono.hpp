#include <bit>
#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    u32 totalNumbers(const std::vector<int>& digits) noexcept
    {
        u32 f[10]{}, r{};
        u32 b{};
        for (int digit : digits)
        {
            ++f[digit];
            b |= (1u << digit);
        }

        for (int i = 0; i != 10; i += 2)
        {
            if (!f[i]) continue;

            for (int j = 0; j != 10; ++j)
            {
                u32 t = 2 + (i == j);
                u32 m1 = u32{f[i] < t} << i;
                u32 m2 = u32{f[j] < t} << j;
                u32 m3 = -u32{f[j] < (t - 1)};
                r += std::popcount(b & (~(1u | m1 | m2 | m3))) & 15;
            }
        }

        return r;
    }
};
