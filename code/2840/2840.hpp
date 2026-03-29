// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/

#include <algorithm>
#include <ranges>
#include <string>

inline static constexpr auto all_equal_to =
    [] [[nodiscard, gnu::always_inline]] (auto&& rng, auto&& value) noexcept
{
    return std::ranges::all_of(
        rng,
        [&] [[gnu::always_inline]] (const auto& x) { return x == value; });
};

class Solution
{
public:
    bool checkStrings(std::string& s1, std::string& s2)
    {
        int f[2][26]{};
        for (bool i = 0; auto [a, b] : std::views::zip(s1, s2))
        {
            ++f[i][a - 'a'];
            --f[i][b - 'a'];
            i = !i;
        }

        return all_equal_to(f[0], 0) && all_equal_to(f[1], 0);
    }
};
