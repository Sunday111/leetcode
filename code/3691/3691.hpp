#include <algorithm>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"

template <typename T>
class SparseTable
{
    inline static std::pair<T, T> st[50000 * 16];
    u32 n;

public:
    SparseTable(const std::vector<u32>& data) noexcept
    {
        n = data.size() & ~u32{};

        u32 max_k = (31 - std::countl_zero(n) + 1) & 63;

        for (u32 i = 0; i < n; i++)
        {
            st[i] = {data[i], data[i]};
        }

        for (u32 k = 1; k < max_k; k++)
        {
            for (u32 i = 0; i + (1 << k) <= n; i++)
            {
                auto [a, b] = st[(k - 1) * n + i];
                auto [c, d] = st[(k - 1) * n + i + (1u << (k - 1))];
                st[k * n + i] = {std::min(a, c), std::max(b, d)};
            }
        }
    }

    [[gnu::always_inline]]
    std::pair<u32, u32> queryMinMax(u32 l, u32 r) const noexcept
    {
        u32 k = (31 - std::countl_zero(r - l + 1u)) & 63, t = r - (1u << k) + 1;
        auto [a, b] = st[k * n + l];
        auto [c, d] = st[k * n + t];
        return {std::min(a, c), std::max(b, d)};
    }
};

class Solution
{
public:
    u64 maxTotalValue(const std::vector<int>& nums, u32 k)
    {
        auto& a = reinterpret_cast<const std::vector<u32>&>(nums);
        u32 n = static_cast<u32>(nums.size()), qs = n - 1;

        if (n < 2) return 0;

        {
            auto [lo, hi] = std::ranges::minmax_element(a);
            u32 i = static_cast<u32>(std::distance(a.begin(), lo));
            u32 j = static_cast<u32>(std::distance(a.begin(), hi));
            u64 x = n - std::max(i, j);

            for (auto u = std::max(i, j); u != n; ++u)
            {
                if (a[u] == a[i]) i = u;
                if (a[u] == a[j]) j = u;
                x += std::min(i, j);
            }

            if (x >= k) return (*hi - *lo) * u64{k};
        }

        SparseTable<u32> st(a);

        static std::pair<u32, u32> q[50000];

        for (u32 i = 0; i != qs; ++i) q[i] = {i, qs};

        u64 s = 0;

        auto range_value =
            [&st] [[gnu::always_inline]] (u32 i, u32 j) noexcept -> u32
        {
            auto [lo, hi] = st.queryMinMax(i, j);
            return hi - lo;
        };

        auto proj =
            [&] [[gnu::always_inline]] (std::pair<u32, u32> t) noexcept -> u32
        {
            return apply(range_value, t);
        };

        constexpr auto cmp = std::less{};

        std::ranges::make_heap(q, q + qs, cmp, proj);

        while (k && qs)
        {
            std::ranges::pop_heap(q, q + qs, cmp, proj);

            auto& [i, j] = q[qs - 1];
            u32 v = range_value(i, j);
            u32 stop = proj(*q);

            // drain this range until its value
            // becomes smaller than the value of the
            // next range in the priority queue
            while (!cmp(v, stop) && i < j && k)
            {
                s += v;
                --j;
                v = range_value(i, j);
                --k;
            }

            qs -= i == j;

            if (i != j) std::ranges::push_heap(q, q + qs, cmp, proj);
        }

        return s;
    }
};
