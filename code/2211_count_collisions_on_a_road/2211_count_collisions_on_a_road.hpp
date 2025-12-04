#include <string_view>

class Solution
{
public:
    [[nodiscard]] static constexpr int countCollisions(
        std::string_view directions) noexcept
    {
        int s = 0, r = 0, a = 0;
        for (char c : directions)
        {
            int bl = c == 'L', br = c == 'R';
            s |= !bl || r;
            a += (s & -bl) + (r & -!br);
            (r += br) &= -br;
        }
        return a;
    }
};
