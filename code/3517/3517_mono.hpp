#include <algorithm>
#include <concepts>
#include <ranges>
#include <string>
#include <type_traits>




inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return b ^ ((a ^ b) & static_cast<T>(-c));
};
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    using u32 = uint32_t;

    [[gnu::target("bmi2,avx2")]]
    std::string smallestPalindrome(std::string& s) noexcept
    {
        u32 f[26]{}, odd = 0;
        for (char c : s) f[c - 'a'] += 1;

        char* out = s.data();
        for (u32 c = 0; c != 26; ++c)
        {
            u32 x = f[c];
            odd = iif(x & 1, c, odd);
            x >>= 1;
            std::fill_n(out, x, static_cast<char>(c + 'a'));
            out += x;
        }

        *out = static_cast<char>(odd + 'a');
        out += s.size() & 1;

        std::ranges::copy(
            std::string_view{s}.substr(0, s.size() / 2) | std::views::reverse,
            out);

        return std::move(s);
    }
};
