#include <string>

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;
    u32 numDecodings(std::string& s) noexcept
    {
        for (char& c : s) c -= '0';
        u8 n = s.size() & 0xFF, i = 0;
        u32 memo[101];
        constexpr u32 kTODO = 0xFFFFFFFF;
        std::fill_n(memo, n, kTODO);
        memo[n] = 1;
        auto dfs = [&](auto& self) -> u32
        {
            auto& r = memo[i];
            if (r == kTODO)
            {
                r = 0;
                if (u8 a = s[i] & 0xF; a)
                {
                    ++i;
                    r = self(self);
                    if (i != n)
                    {
                        u8 v = (a * 10 + s[i]) & 0xFF;
                        if (v > 0 && v < 27)
                        {
                            ++i;
                            r += self(self);
                            --i;
                        }
                    }
                    --i;
                }
            }

            return r;
        };

        return dfs(dfs);
    }
};
