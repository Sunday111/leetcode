#include <algorithm>
#include <cstdint>
#include <cstdlib>

class SolutionMSB
{
private:
    using i32 = int32_t;
    using u32 = uint32_t;
    using i64 = int64_t;
    using u8 = uint8_t;

    static constexpr u32 divide_u(u32 a, u32 b) noexcept
    {
        u32 r = 0;
        for (i32 i = std::countl_zero(b) - std::countl_zero(a); b <= a; --i)
        {
            u32 shifted = b << i;
            bool ok = shifted <= a;
            a -= ok ? shifted : 0;
            u32 t = u32{1} << i;
            r |= ok ? t : 0;
        }
        return r;
    }

public:
    static constexpr i32 divide(i64 a, i64 b) noexcept
    {
        const i64 r = divide_u(
            static_cast<u32>(std::abs(a)),
            static_cast<u32>(std::abs(b)));
        return static_cast<i32>(std::clamp<i64>(
            ((a < 0) ^ (b < 0)) ? -r : r,
            std::numeric_limits<i32>::lowest(),
            std::numeric_limits<i32>::max()));
    }
};
