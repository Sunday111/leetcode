#include <array>
#include <vector>


class Solution
{
public:
    inline static constexpr auto g = []
    {
        std::array<int, 36> r;  // NOLINT
        size_t b = 0, n = 0;
        for (int i = 1; i != 9; ++i)
        {
            r[n++] = i * 11 + 1;
        }
        for (int t = 0; t != 7; ++t)
        {
            for (auto e = n; b != e; ++b)
            {
                auto v = r[b], d = v % 10;
                if (d != 9)
                {
                    r[n++] = v * 10 + d + 1;
                }
            }
        }
        return r;
    }();
    auto sequentialDigits(int low, int high) const noexcept
    {
        // g is a very small array - linear search is likely to be faster.
        size_t b = 0;
        while (b != g.size() && g[b] < low) ++b;
        size_t e = b;
        while (e != g.size() && g[e] <= high) ++e;
        return std::vector<int>{&g[b], &g[e]};
    }
};
