#include <algorithm>
#include <cstdint>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

class Solution
{
public:
    using u32 = uint32_t;

    [[nodiscard]] FORCE_INLINE static constexpr u32 dist(
        const std::vector<int>& query) noexcept
    {
        return static_cast<u32>(std::abs(query[0]) + std::abs(query[1]));
    }

    static std::vector<int> resultsArray(
        const std::vector<std::vector<int>>& queries,
        const u32 k) noexcept
    {
        std::vector<int> r;
        r.reserve(queries.size());
        r.resize(std::min<size_t>(k - 1, queries.size()), -1);
        if (k > queries.size()) return r;

        static u32 q[100'002];                // NOLINT
        const auto qe = q + k, qe1 = qe - 1;  // NOLINT
        for (u32 i = 0; i != k; ++i) q[i] = dist(queries[i]);
        std::ranges::make_heap(q, qe);

        r.push_back(static_cast<int>(q[0]));

        while (r.size() != queries.size())
        {
            if (u32 v = dist(queries[r.size()]); v < q[0])
            {
                std::ranges::pop_heap(q, qe);
                *qe1 = v;
                std::ranges::push_heap(q, qe);
            }

            r.push_back(static_cast<int>(q[0]));
        }

        return r;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
