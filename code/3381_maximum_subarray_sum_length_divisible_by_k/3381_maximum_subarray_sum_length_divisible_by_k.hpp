#include <numeric>
#include <vector>

class Solution
{
public:
    using ll = long long;
    using u32 = uint32_t;
    [[nodiscard]] static constexpr ll maxSubarraySum(
        const std::vector<int>& nums,
        u32 k) noexcept
    {
        static ll p[200'000];
        auto d = nums.data(), end = d + nums.size();
        std::inclusive_scan(d, d + k, p, std::plus<ll>{}, 0LL);
        ll s = p[k - 1], r = s;
        p[k - 1] = std::min(s, 0LL);
        d += k;
        for (u32 m = 0; d != end; ++m)
        {
            m &= -u32{m != k};
            s += *(d++);
            ll& mp = p[m];
            r = std::max(r, s - mp);
            mp = std::min(mp, s);
        }

        return r;
    }
};
