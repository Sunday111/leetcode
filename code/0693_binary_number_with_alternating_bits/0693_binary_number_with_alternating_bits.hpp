#include <bit>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr bool hasAlternatingBits(u32 n) noexcept
    {
        int s = std::countl_zero(n);
        u32 a = 0xAAAAAAAAu >> s;
        u32 b = 0x55555555u >> s;
        return n == a || n == b;
    }
};
