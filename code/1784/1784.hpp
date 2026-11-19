#include <string>

class Solution
{
public:
    [[nodiscard]] constexpr bool checkOnesSegment(const std::string& s) noexcept
    {
        auto p = s.data();
        while (*p == '1') ++p;
        while (*p == '0') ++p;
        return !*p;

        // Another options:
        // return ranges::empty(ranges::search(s, "01"sv));
        // return !ranges::contains(views::adjacent<2>(s), tuple{'0','1'});
    }
};
