#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr bool judgeCircle(std::string_view moves) noexcept
    {
        int x = 0, y = 0;
        for (char c : moves)
        {
            y += (c == 'U') - (c == 'D');
            x += (c == 'R') - (c == 'L');
        }

        return x == 0 && y == 0;
    }
};
