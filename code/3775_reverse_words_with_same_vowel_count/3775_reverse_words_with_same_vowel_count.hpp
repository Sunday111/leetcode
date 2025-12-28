#include <algorithm>
#include <string>

class Solution
{
public:
    using u32 = uint32_t;

    static constexpr std::string_view kVowelsList = "aeiou";

    inline static constexpr u32 kVowelsBits = []
    {
        u32 b = 0;
        for (char c : kVowelsList) b |= (1u << ((c - 'a') & 0xFF));
        return b;
    }();

    [[nodiscard]] static constexpr std::string reverseWords(
        std::string& s) noexcept
    {
        u32 target = 0, current = 0;

        auto i = s.begin(), e = s.end();

        for (; i != e && *i != ' '; ++i)
        {
            target += ((1u << ((*i - 'a') & 0xFF)) & kVowelsBits) != 0;
        }

        // there is more than one word
        auto wb = std::min(i + 1, e);
        for (; i != e; ++i)
        {
            char c = *i;
            if (c == ' ')
            {
                if (target == current) std::reverse(wb, i);
                wb = i + 1;
                current = 0;
            }
            else
            {
                current += ((1u << ((c - 'a') & 31)) & kVowelsBits) != 0;
            }
        }

        if (target == current) std::reverse(wb, e);

        return std::move(s);
    }
};
