#include <algorithm>
#include <cstdint>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[gnu::always_inline]]
    static u8 waviness(u32 x) noexcept
    {
        u8 d[5];
        u8 n = 0;
        while (x)
        {
            d[n++] = x % 10;
            x /= 10;
        }

        auto tst = [&] [[gnu::always_inline]] (u8 i)
        {
            u8 l = d[i + 1], v = d[i], r = d[i - 1];
            return (i + 1 < n) & (v != l) & (v != r) & ((v < l) == (v < r));
        };

        return (tst(1) + tst(2) + tst(3)) & 0xF;
    }
    u32 totalWaviness(u32 num1, u32 num2) noexcept
    {
        num2 = std::min(num2 + 1, 100000u);
        u32 r = 0;
        while (num2-- != num1) r += waviness(num2);
        return r;
    }
};
