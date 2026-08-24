#include <bitset>
#include <vector>


class Solution
{
public:
    auto missingMultiple(std::vector<int>& nums, unsigned k)
    {
        std::bitset<128> b;
        for (int x : nums) b[x & 127] = 1;
        auto t = k;
        while (t < 128 && b[t]) t += k;
        return t;
    }
};
