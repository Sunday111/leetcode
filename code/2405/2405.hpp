#include <string>

class Solution
{
public:
    using u32 = uint32_t;
    u32 partitionString(const std::string& s)
    {
        u32 r = 1, b = 0;
        for (char c : s)
        {
            u32 m = 1u << (c - 'a');
            bool t = b & m;
            r += t;
            b &= -u32{!t};
            b |= m;
        }
        return r;
    }
};
