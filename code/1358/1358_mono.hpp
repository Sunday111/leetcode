#include <string>


class Solution
{
public:
    using u32 = uint32_t;
    u32 numberOfSubstrings(const std::string& s) noexcept
    {
        const u32 n = static_cast<u32>(s.size());
        u32 a = 0, z = 3, f[3] = {0};
        for (u32 i = 0, j = 0; j != n; ++j)
        {
            z -= ++f[s[j] - 'a'] == 1;
            while (!z) z += !--f[s[i++] - 'a'];
            a += i;
        }
        return a;
    }
};
