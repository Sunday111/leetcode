#include <bitset>
#include <vector>

class Solution
{
public:
    [[nodiscard]] int repeatedNTimes(const std::vector<int>& nums) noexcept
    {
        std::bitset<10000> b;
        for (int v : nums)
        {
            if (b[v & 0xFFFF]) return v;
            b[v & 0xFFFF] = 1;
        }

        std::unreachable();
    }
};
