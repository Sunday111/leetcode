#include <cstdint>
#include <string>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] auto minFlips(const std::string& str) noexcept
    {
        auto s = reinterpret_cast<const u8*>(str.data());
        u32 n = static_cast<u32>(str.size()), f = 0;
        for (u32 i = 0; i != n; ++i)
        {
            f += (i ^ s[i]) & 1u;
        }

        u32 r = std::min(f, n - f);
        if (n & 1)
        {
            for (u32 i = 0; i != n; ++i)
            {
                f += 1 - 2 * ((s[i] ^ i) & 1);
                r = std::min(r, f), r = std::min(r, n - f);
            }
        }

        return r;
    }
};
