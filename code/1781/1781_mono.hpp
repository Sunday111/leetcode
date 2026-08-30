#include <algorithm>
#include <concepts>
#include <cstdint>
#include <string_view>
#include <type_traits>
#include <utility>




inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return b ^ ((a ^ b) & static_cast<T>(-c));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    u32 f[26]{};

    [[nodiscard,
      gnu::always_inline,
      gnu::target("bmi2,avx2")]] constexpr std::pair<u32, u32>
    minmax() const noexcept
    {
        u32 lo{~u32{}}, hi{0};
        for (auto v : f)
        {
            lo = iif(v, std::min(lo, v), lo);
            hi = std::max(hi, v);
        }
        return {lo, hi};
    }

    [[nodiscard, gnu::target("bmi2,avx2"), gnu::always_inline]] constexpr u32
    beauty() const noexcept
    {
        auto [lo, hi] = minmax();
        return hi - lo;
    }

    [[gnu::target("bmi2,avx2")]]
    constexpr u32 beautySum(std::string_view s) noexcept
    {
        const u32 n = static_cast<u32>(s.size());
        const u32 n1 = n - 1;

        u32 r{};

        u32 i = 0, j = 0;

        while (i != n1)
        {
            if (i & 1)
            {
                while (j != i)
                {
                    r += beauty();
                    --f[s[--j] - 'a'];
                }
                j = ++i;
            }
            else
            {
                while (j != n)
                {
                    ++f[s[j++] - 'a'];
                    r += beauty();
                }
                --f[s[i++] - 'a'];
            }
        }

        return r;
    }
};
