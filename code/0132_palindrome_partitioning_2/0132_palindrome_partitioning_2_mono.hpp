#include <concepts>
#include <cstdint>
#include <string_view>
#include <utility>







#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
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
    static constexpr u32 kTableWidth = 2000;
    static constexpr u32 kBitsetCapacity = (2000 * kTableWidth) / 8;
    inline static u64 words[kBitsetCapacity];

    [[nodiscard]] FORCE_INLINE static constexpr u64
    set_bit(u64 bs, u8 i, bool value) noexcept
    {
        u64 a = (u64{1} << i) | bs;
        u64 b = (~(u64{1} << i)) & bs;
        return iif(value, a, b);
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool get_bit(
        u64 bs,
        u8 i) noexcept
    {
        return bs & (u64{1} << i);
    }

    FORCE_INLINE static constexpr void
    set_is_palindrome(u16 i, u16 j, bool value) noexcept
    {
        u32 row_offset = i * kTableWidth;
        u32 global_bit_index = row_offset + j;
        u32 word_index = global_bit_index / 64;
        u8 bit_index = global_bit_index & 63;
        words[word_index] = set_bit(words[word_index], bit_index, value);
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool get_is_palindrome(
        u16 i,
        u16 j) noexcept
    {
        u32 row_offset = i * kTableWidth;
        u32 global_bit_index = row_offset + j;
        u32 word_index = global_bit_index / 64;
        u8 bit_index = global_bit_index & 63;
        return get_bit(words[word_index], bit_index);
    }

    FORCE_INLINE static int minCut(std::string_view s) noexcept
    {
        static u16 min_num_dp[2001];

        const u16 n = s.size() & 0xFFFF;
        min_num_dp[n] = 0;

        if (n > 1)
        {
            // length is 2
            for (u16 i = 0, j = i + 1; j != n; ++i, ++j)
            {
                set_is_palindrome(i, j, s[i] == s[j]);
            }
        }

        if (n > 2)
        {
            // length is 3
            for (u16 i = 0, j = i + 2; j != n; ++i, ++j)
            {
                set_is_palindrome(i, j, s[i] == s[j]);
            }
        }

        // length > 3
        if (n > 3)
        {
            for (u16 diff = 3; diff != n; ++diff)
            {
                for (u16 i = 0, j = i + diff; j != n; ++i, ++j)
                {
                    set_is_palindrome(
                        i,
                        j,
                        (s[i] == s[j]) && get_is_palindrome(i + 1, j - 1));
                }
            }
        }

        auto isPalindrome = [&](u16 first, u16 last)
        {
            return get_is_palindrome(first, last) || (first == last);
        };

        for (u16 i = n; i--;)
        {
            auto& dpi = min_num_dp[i] = min_num_dp[i + 1] + 1;

            for (u16 j = i + 1; j != n; ++j)
            {
                if (isPalindrome(i, j))
                {
                    dpi = std::min<u16>(dpi, min_num_dp[j + 1] + 1);
                }
            }
        }

        return min_num_dp[0] - 1;
    }
};
