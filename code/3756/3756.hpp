#include <string_view>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    static constexpr u32 kMOD = 1'000'000'007;

    inline static u32 ps[100'002], pn[100'002], remap[100'001];
    inline static const auto kPowers = []()
    {
        std::array<u32, 100'001> powers;  // NOLINT
        u32 i = 0;
        for (u64 x = 1; i != powers.size(); (x *= 10) %= kMOD)
        {
            powers[i++] = static_cast<u32>(x);
        }
        powers[0] = 0;
        return powers;
    }();

    std::vector<int> sumAndMultiply(
        std::string_view s,
        const std::vector<std::vector<int>>& queries) noexcept
    {
        const u32 n = static_cast<u32>(s.size());

        u32 m = 0, sum = 0;
        u64 num = 0;
        for (u32 i = 0; i != n; ++i)
        {
            remap[i] = m;
            char c = s[i];
            u32 d = (c - '0') & 0xF;

            if (!d) continue;

            ps[m] = sum;
            sum += d;

            pn[m] = cast<u32>(num);
            ((num *= 10) += d) %= kMOD;

            ++m;
        }
        ps[m] = sum;
        pn[m] = cast<u32>(num);
        remap[n] = m;

        std::vector<int> ans;
        ans.reserve(queries.size());
        for (auto& query :
             reinterpret_cast<const std::vector<std::vector<u32>>&>(queries))
        {
            u32 b = remap[query[0]];
            u32 e = remap[query[1] + 1];
            u64 rng_sum = ps[e] - ps[b];
            u64 rng_num = (u64{pn[e]} + kMOD -
                           (u64{pn[b]} * u64{kPowers[e - b]}) % kMOD) %
                          kMOD;
            ans.push_back(static_cast<int>((rng_sum * rng_num) % kMOD));
        }

        return ans;
    }
};
