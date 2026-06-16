#include <algorithm>
#include <string>


class Solution
{
public:
    inline static char x[(2 << 21) + 1];  // NOLINT
    [[gnu::target("avx2,bmi2")]]
    std::string processStr(const std::string& s) noexcept
    {
        int t[2];
        t[0] = t[1] = std::ranges::size(x) / 2;
        bool rev = false;
        for (char c : s)
        {
            int n[2];
            n[0] = t[1] - t[0];
            n[1] = -n[0];
            switch (c)
            {
            case '*':
                t[0] += rev & !!n[0];
                t[1] -= !rev & !!n[0];
                break;

            case '#':
                std::ranges::copy_n(x + t[0], n[0], x + t[0] + n[rev]);
                t[!rev] += n[rev];
                break;

            case '%':
                rev = !rev;
                break;

            default:
                t[0] -= rev;
                x[t[!rev]] = c;
                t[1] += !rev;
                break;
            }
        }

        std::string out;
        out.reserve(static_cast<size_t>(t[1] - t[0]));
        if (rev)
        {
            out.insert(
                out.end(),
                std::make_reverse_iterator(x + t[1]),
                std::make_reverse_iterator(x + t[0]));
        }
        else
        {
            out.insert(out.end(), x + t[0], x + t[1]);
        }
        return out;
    }
};
