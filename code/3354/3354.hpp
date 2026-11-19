#include <vector>

class Solution
{
public:
    int countValidSelections(std::vector<int>& nums)
    {
        int t = 0;
        for (int v : nums) t += v;
        int s = 0, r = 0;
        for (int v : nums)
        {
            s += v << 1;
            int d = abs(s - t);
            r += std::max(2 - d, 0) & (!!v - 1);
        }
        return r;
    }
};
