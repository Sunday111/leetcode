#include <array>
#include <ranges>
#include <string_view>

class Solution
{
public:
    using u32 = uint32_t;
    static constexpr auto freqArray(std::string_view s) noexcept
    {
        std::array<u32, 26> r{};
        for (char c : s) ++r[(c - 'a') & 31];
        return r;
    }
    auto maxNumberOfBalloons(std::string_view text) noexcept
    {
        constexpr std::string_view word = "balloon";
        auto has = freqArray(text), need = freqArray(word);
        u32 r = ~u32{};
        for (auto [a, b] : std::views::zip(has, need))
        {
            if (b) r = std::min(r, a / b);
        }

        return r;
    }
};
