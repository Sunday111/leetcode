#pragma once

#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
    std::vector<int> productQueries(
        uint32_t n,
        std::vector<std::vector<int>>& queries)
    {
        std::vector<int> r;
        r.resize(queries.size(), 1);

        for (size_t i = 0; i != queries.size(); ++i)
        {
            auto& q = queries[i];
            int left = q[0], right = q[1];
            uint32_t np = 0;
            std::array<uint32_t, 32> powers;  // NOLINT
            std::ranges::fill(powers, 1);
            for (uint32_t j = 0; j != 32; ++j)
            {
                if (uint32_t t = 1u << j; t & n) powers[np++] = t;
            }

            int& v = r[i];
            for (int j = left; j <= right; ++j)
            {
                int64_t tmp = v;
                tmp *= static_cast<int64_t>(powers[static_cast<uint32_t>(j)]);
                tmp %= 1'000'000'007;
                v = static_cast<int>(tmp);
            }
        }
        return r;
    }
};
