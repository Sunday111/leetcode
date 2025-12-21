#include <string_view>

#include "int_if.hpp"
#include "integral_aliases.hpp"

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

        for (u16 diff = 1; diff != n; ++diff)
        {
            if (diff < 3)
            {
                for (u16 i = 0, j = i + diff; j != n; ++i, ++j)
                {
                    set_is_palindrome(i, j, s[i] == s[j]);
                }
            }
            else
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

        for (u16 i = n; i--;)
        {
            auto& dpi = min_num_dp[i] = min_num_dp[i + 1] + 1;

            for (u16 j = i + 1; j != n; ++j)
            {
                if (get_is_palindrome(i, j))
                {
                    dpi = std::min<u16>(dpi, min_num_dp[j + 1] + 1);
                }
            }
        }

        return min_num_dp[0] - 1;
    }
};
