#include <vector>

class Solution
{
public:
    [[gnu::always_inline]] static constexpr int pack(int f, int v) noexcept
    {
        return (f << 20) | v;
    }
    [[gnu::always_inline]] static constexpr auto unpack(int x) noexcept
    {
        return std::pair{x >> 20, ((1 << 20) - 1) & x};
    }

    auto findDuplicates(std::vector<int>& aa) noexcept
    {
        auto a = aa.data();
        for (int x : aa)
        {
            int i = unpack(x - 1).second;
            auto [f, v] = unpack(a[i]);
            a[i] = pack(f + 1, v);
        }
        int k = 0, n = static_cast<int>(aa.size());
        for (int i = 0; i != n; ++i)
        {
            auto [f, v] = unpack(a[i]);
            a[k] = i + 1;
            k += f == 2;
        }
        aa.resize(static_cast<size_t>(k));
        return std::move(aa);
    }
};
