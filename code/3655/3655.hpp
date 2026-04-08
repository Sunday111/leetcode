#include <algorithm>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    inline static constexpr u32 kMOD = 1'000'000'007;
    inline static u32 inv[100001];

    [[nodiscard, gnu::always_inline]] constexpr static u32 mm(
        u32 a,
        u32 b) noexcept
    {
        return static_cast<u32>((u64{a} * b) % kMOD);
    }

    [[gnu::always_inline]] constexpr static u32& mme(u32& x, u32 m) noexcept
    {
        return x = mm(x, m);
    }

    inline static const auto _init_ = []
    {
        inv[1] = 1;
        for (u32 v = 2; v != 100000; v++)
        {
            inv[v] = mm(kMOD - (kMOD / v), inv[kMOD % v]);
        }

        return 0;
    }();

    [[nodiscard]] static u32 xorAfterQueriesImpl(
        std::vector<u32>& nums,
        std::vector<std::vector<u32>>& queries_) noexcept
    {
        const u32 n = static_cast<u32>(nums.size()), ns = n / 650;

        struct Q
        {
            u32 l, r, k, v;
        };

        auto brute_force = [&](Q& q)
        {
            while (q.l <= q.r)
            {
                mme(nums[q.l], q.v);
                q.l += q.k;
            }
        };

        u32 qn = 0;
        static Q queries[100'001];
        for (auto& q : queries_)
        {
            auto& x = queries[qn] = {
                .l = q[0],
                .r = q[1],
                .k = q[2],
                .v = q[3],
            };

            if (x.v == 1) continue;

            if (x.k > ns || ((x.r - x.l) / x.k < 500))
            {
                brute_force(x);
            }
            else
            {
                ++qn;
            }
        }

        std::ranges::sort(queries, queries + qn, std::less{}, &Q::k);

        for (u32 qb = 0, qe = 0; qe != qn;)
        {
            u32 k = queries[qb].k;
            long u = 0;
            while (qe != qn && queries[qe].k == k)
            {
                u += queries[qe].r + 1 - queries[qe].l;
                ++qe;
            }

            // small number of queries with the same k
            // brute force might still win
            if (std::cmp_less(u, n * 4))
            {
                while (qb != qe) brute_force(queries[qb++]);
                continue;
            }

            static u32 gmul[100'001];
            if (!gmul[0]) std::ranges::fill(gmul, 1);

            while (qb != qe)
            {
                auto& x = queries[qb];
                mme(gmul[x.l], x.v);
                u32 stop = std::min(n, x.l + ((x.r - x.l) / x.k + 1) * x.k);
                mme(gmul[stop], inv[x.v]);
                ++qb;
            }

            auto lmul = reinterpret_cast<u32*>(alloca(4 * k));
            std::fill_n(lmul, k, 1);
            for (u32 i = 0, j = 0; i != n; ++i)
            {
                auto& x = nums[i];
                j &= -u32{j != k};  // j = i % k
                mme(x, mme(lmul[j++], std::exchange(gmul[i], 1)));
            }

            gmul[n] = 1;
        }

        return std::ranges::fold_left(nums, 0, std::bit_xor{});
    }

    [[nodiscard]] int xorAfterQueries(
        std::vector<int>& nums,
        std::vector<std::vector<int>>& queries) const noexcept
    {
        return static_cast<int>(xorAfterQueriesImpl(
            reinterpret_cast<std::vector<u32>&>(nums),
            reinterpret_cast<std::vector<std::vector<u32>>&>(queries)));
    }
};

#include "sync_stdio.hpp"
