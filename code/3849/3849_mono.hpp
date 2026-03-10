#include <cstdint>
#include <string>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] std::string maximumXor(
        std::string& s,
        const std::string& t) noexcept
    {
        u32 c1 = 0, c2 = 0, n = static_cast<u32>(t.size());
        for (u32 i = 0; i != n; i++)
        {
            c1 += !(s[i] & 1);
            c2 += t[i] & 1;
        }
        if (c2 <= c1)
        {
            for (u32 i = 0; c2; i++)
            {
                bool x = !(s[i] & 1);
                s[i] |= x;  // NOLINT
                c2 -= x;
            }
        }
        else
        {
            u32 f[]{n - c2, c2};
            for (char& c : s)
            {
                bool k = c & 1;
                bool g = f[!k];
                c = '0' | g;  // NOLINT
                --f[g ^ k];
            }
        }
        return std::move(s);
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
