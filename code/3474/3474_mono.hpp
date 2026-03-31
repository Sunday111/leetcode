#include <concepts>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>




// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard, gnu::always_inline]] constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    std::string generateString(
        const std::string& str1,
        const std::string& str2) noexcept
    {
        constexpr u8 m = 0b10000000, blank = m | 'a';

        const u16 l1 = str1.size() & 0xFFFF;
        const u16 l2 = str2.size() & 0xFFFF;
        const u16 n = l1 + l2 - 1;
        std::string result(l1 + l2 - 1, std::bit_cast<char>(blank));

        const u8* s1 = reinterpret_cast<const u8*>(str1.data());
        const u8* s2 = reinterpret_cast<const u8*>(str2.data());
        u8* r = reinterpret_cast<u8*>(result.data());

        for (u32 i = 0; i != l1; ++i)
        {
            if (str1[i] != 'T') continue;
            for (u32 j = 0; j != l2; ++j)
            {
                auto c = exch(r[i + j], s2[j]);
                [[unlikely]] if (c != blank && c != s2[j])
                {
                    return "";
                }
            }
        }

        for (u16 i = 0; i != l1; ++i)
        {
            if (s1[i] != 'F')
            {
                r[i] &= ~m;
                continue;
            }

            bool eq = true;
            constexpr u16 kInvalid = static_cast<u16>(~u16{});
            u16 replace = kInvalid;
            for (u16 j = 0; j != l2 && eq; ++j)
            {
                u16 k = i + j;
                eq = (r[k] | m) == (s2[j] | m);
                replace = iif(r[k] & m, k, replace);
            }

            if (!eq)
            {
                r[i] &= ~m;
                continue;
            }

            [[unlikely]] if (replace == kInvalid)
            {
                return "";
            }

            r[replace] = 'b' | m;
            r[i] &= ~m;
        }

        // remove blank bit from the tail
        for (u16 i = l1; i != n; ++i) r[i] &= ~m;

        return result;
    }
};
