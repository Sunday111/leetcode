#include <vector>

class Solution
{
public:
    bool isOneBitCharacter(std::vector<int>& bits)
    {
        uint32_t n = (bits.size() - 1) & 0xFFFF, t = 0;
        for (uint32_t i = 0; i != n; ++i) t = (!t) & bits[i] & 0x1;
        return !t;
    }
};
