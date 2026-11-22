#include <climits>
#include <vector>

class Solution
{
public:
    static bool uniformArray(const std::vector<int>& a)
    {
        int lo{INT_MAX}, x{};
        for (auto v : a)
        {
            x += v & 1;
            lo = std::min(lo, v);
        }
        return (lo & 1) | !x;
    }
};
