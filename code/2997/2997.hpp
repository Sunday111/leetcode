#include <bit>
#include <vector>

class Solution
{
public:
    int minOperations(std::vector<int>& nums, unsigned k)
    {
        for (int v : nums) k ^= std::bit_cast<unsigned>(v);
        return std::popcount(k);
    }
};
