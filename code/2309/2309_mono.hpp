#include <cstdint>
#include <string>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    std::string greatestLetter(std::string& s)
    {
        u32 b[2]{};
        for (char c : s)
        {
            bool t = c < 'a';
            b[t] |= u32{1} << (c - ('a' - (t << 5)));
        }
        u32 x = std::countl_zero(b[0] & b[1]) & 63;
        s[0] = static_cast<char>('`' - x);
        s.resize(x < 32);
        return std::move(s);
    }
};
