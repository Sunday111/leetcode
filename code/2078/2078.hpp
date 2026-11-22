#include <vector>

class Solution
{
public:
    static auto maxDistance(std::vector<int>& c) noexcept
    {
        size_t n = c.size();
        size_t i = 0, j = n - 1;
        while (c[i] == c[0] && c[j] == c[0])
        {
            ++i;
            --j;
        }
        return j;
    }
};

