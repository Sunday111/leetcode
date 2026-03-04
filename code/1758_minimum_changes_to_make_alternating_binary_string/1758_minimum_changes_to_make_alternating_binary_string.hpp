#include <string>

class Solution
{
public:
    [[nodiscard]] constexpr int minOperations(const std::string& s) noexcept
    {
        using u16 = uint16_t;
        u16 t = 0, n = s.size() & 0xFFFF;
        for (u16 i = 0; i != n; ++i) t += 1 & ~(s[i] ^ i);
        return std::min<u16>(t, n - t);
    }
};
