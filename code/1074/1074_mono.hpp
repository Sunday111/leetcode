#include <bit>
#include <cstdint>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};



#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard]] FORCE_INLINE constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}


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
    u32 numSubmatrixSumTarget(std::vector<std::vector<int>>& orig, int target)
    {
        static i32 g[1024 * 1024];

        const u16 h = cast<u16>(orig.size()), w = cast<u16>(orig[0].size());

        u8 stride = std::bit_width(w + 1u) & 15;

        auto gg = [&] [[nodiscard, gnu::always_inline]] (
                      u16 x,
                      u16 y) noexcept -> decltype(auto)
        {
            return g[(u32{y} << stride) | u32{x}];
        };

        for (u16 y = 0; y != h; ++y)
        {
            for (u16 x = 0; x != w; ++x)
            {
                gg(x, y) = orig[y][x];
            }
        }

        // row prefix sum
        for (u16 y = 0; y != h; ++y)
        {
            // each row prefix sum starts with zero
            // which helps to reduce branches later
            i32 s = 0;
            for (u16 x = 0; x != w; ++x)
            {
                s += exch(gg(x, y), s);
            }
            gg(w, y) = s;
        }

        u16 w1 = w + 1;
        u32 r = 0;
        std::unordered_map<int, u32> f;
        f.reserve(h * 2);

        for (u16 x_begin = 0; x_begin != w; ++x_begin)
        {
            for (u16 x_end = x_begin + 1; x_end != w1; ++x_end)
            {
                f.clear();
                f[0] = 1;
                i32 s = 0;

                for (u16 y = 0; y != h; ++y)
                {
                    s += gg(x_end, y) - gg(x_begin, y);
                    auto it = f.find(s - target);
                    r += it == f.end() ? 0 : it->second;
                    f[s]++;
                }
            }
        }

        return r;
    }
};
