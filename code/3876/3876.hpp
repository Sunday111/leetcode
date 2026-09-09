#include <vector>

class Solution
{
public:
    bool uniformArray(const std::vector<int>& a)
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
