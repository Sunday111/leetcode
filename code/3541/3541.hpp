#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>

#include "compose.hpp"
#include "functional.hpp"

class Solution
{
public:
    using u8 = uint8_t;
    using u64 = uint64_t;

    static constexpr auto is_vowel_bitset = []
    {
        u64 bs = 0;
        for (char c : std::string_view{"aeiou"}) bs |= (u64{1} << (c - 64));
        return bs;
    }();

    static constexpr bool is_vowel(char c) noexcept
    {
        return is_vowel_bitset & (uint64_t{1} << (c - 64));
    }

    template <typename To>
    static constexpr auto cast = []<typename From>(From&& from) noexcept
    {
        return static_cast<To>(std::forward<From&&>(from));
    };

    [[nodiscard]] static constexpr int maxFreqSum(std::string_view s) noexcept
    {
        constexpr auto to_u8 = cast<uint8_t>;
        std::array<u8, 64> freq_arr{};
        auto freq = compose(to_u8, index_op(freq_arr));
        for (char c : s) ++freq(c);

        std::array<u8, 2> ans{};

        for (const char c : std::views::iota('a', 'z' + 1))
        {
            auto& r = ans[is_vowel(c)];
            r = std::max(r, freq(c));
        }
        return ans[0] + ans[1];
    }
};
