#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr int minimumDeletions(std::string& s) noexcept
    {
        int r = 0;
        for (int k = 0; char c : s)
        {
            bool b = c == 'a';
            r = std::min(r + b, k);
            k += !b;
        }
        return r;
    }
};
