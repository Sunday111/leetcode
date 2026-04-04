#include <string>



class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard, gnu::hot]] static constexpr std::string decodeCiphertext(
        const std::string& s,
        u32 hs) noexcept
    {
        const u32 n = static_cast<u32>(s.size()), ws = n / hs;
        if (!ws) return "";

        std::string d(n, ' ');
        for (u32 os = 0, ys = 0; ys != hs; os += ws, ++ys)
        {
            for (u32 id = ys, xs = ys; xs != ws; id += hs, ++xs)
            {
                d[id] = s[os + xs];
            }
        }

        d.resize(d.find_last_not_of(' ') + 1);
        return d;
    }
};
