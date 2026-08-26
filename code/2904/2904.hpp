#include <algorithm>
#include <string>

class Solution
{
public:
    using u32 = uint32_t;
    std::string shortestBeautifulSubstring(std::string& s, u32 k) noexcept
    {
        u32 i = 0, j = 0;
        const u32 n = static_cast<u32>(s.size());

        u32 t = 0;
        for (; j != n && t != k;) t += s[j++] & 1;

        if (t != k)
        {
            s.clear();
            return std::move(s);
        }

        std::string_view o = s, r = o.substr(i, j - i);

        auto test = [&]
        {
            while (s[i] == '0') ++i;
            auto x = o.substr(i, j - i);
            if (t == k &&
                (x.size() < r.size() || (x.size() == r.size() && x < r)))
            {
                r = x;
            }
        };

        while (j != n)
        {
            test();
            ++i, --t;
            while (j != n && t != k) t += s[j++] & 1;
        }

        test();

        std::ranges::copy(r, s.begin());
        s.resize(r.size());
        return std::move(s);
    }
};
