#include <algorithm>
#include <string_view>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 maxRepeating(
        const std::string_view sequence,
        const std::string_view word) noexcept
    {
        u32 r = 0;
        for (u32 start = 0; start != sequence.size(); ++start)
        {
            u32 l = 0;
            auto s = sequence.substr(start);
            while (s.starts_with(word))
            {
                ++l;
                s = s.substr(word.size());
            }
            r = std::max(l, r);
        }
        return r;
    }
};
