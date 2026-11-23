#include <cstdint>

class ProductOfNumbers
{
public:
    using u32 = uint32_t;
    inline static u32 p[40'001] = {1};
    u32 n = 0;

    void add(u32 num) noexcept
    {
        [[assume(num <= 100)]];
        num *= p[n];
        p[++n] = num;
        n &= -u32{num != 0};
    }

    int getProduct(u32 k) const noexcept
    {
        u32 m = -u32{k <= n};
        return static_cast<int>((p[n] / p[(n - k) & m]) & m);
    }
};
