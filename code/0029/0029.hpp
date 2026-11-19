#include <algorithm>
#include <cstdint>
#include <cstdlib>

class Solution
{
private:
    using u64 = uint64_t;
    using i32 = int32_t;
    using i64 = int64_t;

    static constexpr u64 divide_u(u64 a, u64 b) noexcept
    {
        u64 r = 0;
        while (b < a)
        {
            u64 k = b;
            u64 q = 1;
            while ((k << 1) <= a)
            {
                k <<= 1;
                q <<= 1;
            }
            a -= k;
            r += q;
        }
        return r + (b == a);
    }

public:
    static constexpr i32 divide(i64 a, i64 b) noexcept
    {
        const auto r = static_cast<i64>(divide_u(
            static_cast<u64>(std::abs(a)),
            static_cast<u64>(std::abs(b))));
        return static_cast<i32>(std::clamp<i64>(
            ((a < 0) ^ (b < 0)) ? -r : r,
            std::numeric_limits<i32>::lowest(),
            std::numeric_limits<i32>::max()));
    }
};
