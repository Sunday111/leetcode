#include <array>

class Solution
{
public:
    using u16 = uint16_t;
    inline static constexpr std::array<u16, 4> kDiv{1, 10, 100, 1000};
    inline static constexpr auto kAns = []
    {
        std::array<u16, 10001> a;  // NOLINT
        for (u16 i = 0, p = 0; i != a.size(); ++i)
        {
            u16 g = 0, b = 0;
            for (u16 j : kDiv)
            {
                u16 shift = (i / j) % 10;
                u16 m = (u16{1} << shift) & 0xFFFF;
                b |= 0b0010011000 & m;
                g |= 0b1001100100 & m;
            }
            a[i] = p += (g && !b);
        }
        return a;
    }();

    constexpr int rotatedDigits(u16 n) noexcept { return kAns[n]; }
};
