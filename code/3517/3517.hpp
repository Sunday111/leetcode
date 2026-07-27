#include <algorithm>
#include <ranges>
#include <string>

#include "int_if.hpp"
#include "sync_stdio.hpp"

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
