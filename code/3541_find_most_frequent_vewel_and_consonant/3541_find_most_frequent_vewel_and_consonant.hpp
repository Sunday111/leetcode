#include <algorithm>
#include <array>
#include <ranges>
#include <string_view>

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

    [[nodiscard]] static constexpr int maxFreqSum(std::string_view s) noexcept
    {
        std::array<u8, 64> freq_arr{};
        auto freq = [&](char c) -> u8&
        {
            return freq_arr[c & 0x7F];
        };
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
