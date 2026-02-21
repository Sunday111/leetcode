#include <bit>
#include <cstdint>
#include <initializer_list>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    inline static constexpr auto kPrimes = []
    {
        u32 m = 0;
        for (auto i : {2, 3, 5, 7, 11, 13, 17, 19}) m |= (1u << i);
        return m;
    }();

    [[nodiscard]] static constexpr u32 countPrimeSetBits(
        u32 left,
        u32 right) noexcept
    {
        u32 r = 0;
        for (u32 x = left, end = right + 1; x != end; ++x)
        {
            r += !!(kPrimes & (1u << std::popcount(x)));
        }

        return r;
    }
};
