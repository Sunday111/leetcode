
#include <string_view>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    static constexpr u32 kMOD = 1'000'000'007;

    std::vector<int> sumAndMultiply(
        std::string_view s,
        std::vector<std::vector<int>>& queries)
    {
        const u32 n = cast<u32>(s.size());

        static auto powers = []()
        {
            std::array<u32, 100'001> powers;  // NOLINT
            u32 i = 0;
            for (u64 x = 1; i != powers.size(); (x *= 10) %= kMOD)
            {
                powers[i++] = cast<u32>(x);
            }
            powers[0] = 0;
            return powers;
        }();

        static u32 ps[100'002], pn[100'002], remap[100'001];

        u32 m = 0;
        u32 sum = 0;
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
            num *= 10;
            num += d;
            num %= kMOD;

            ++m;
        }
        ps[m] = sum;
        pn[m] = cast<u32>(num);
        remap[n] = m;

        std::vector<int> ans;
        ans.reserve(queries.size());
        for (auto& query : queries)
        {
            u32 begin = remap[cast<u32>(query[0])];
            u32 end = remap[cast<u32>(query[1]) + 1];
            u32 num_digits = end - begin;
            u64 sum_in_range = ps[end] - ps[begin];
            u64 num_in_range =
                (u64{pn[end]} + kMOD -
                 (u64{pn[begin]} * u64{powers[num_digits]}) % kMOD) %
                kMOD;
            ans.push_back(cast<int>((sum_in_range * num_in_range) % kMOD));
        }

        return ans;
    }
};
