#include <vector>

class Solution
{
public:
    static bool kLengthApart(const std::vector<int>& nums, int k) noexcept
    {
        if (int z = k)
        {
            for (int v : nums)
            {
                if (v && z < k) return false;
                ++z &= -!v;
            }
        }
        return true;
    }
};
