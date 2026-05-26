#include <bit>
#include <cstdint>
#include <string>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    int numberOfSpecialChars(std::string& word)
    {
        u32 b[2]{};
        for (char c : word)
        {
            bool t = c < 'a';
            b[t] |= u32{1} << (c - ('a' - (t << 5)));
        }
        return std::popcount(b[0] & b[1]);
    }
};
