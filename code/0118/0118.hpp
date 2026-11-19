#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr std::vector<std::vector<int>> generate(
        u32 n) noexcept
    {
        std::vector<std::vector<int>> r;
        r.resize(n);
        r[0] = {1};

        for (u32 i = 1; i != n; ++i)
        {
            auto& row = r[i];
            row.resize(i + 1);
            row[0] = 1;

            auto p = r[i - 1].begin();
            for (u32 j = 1; j != i; ++j)
            {
                int& v = row[j];
                v = *p++;
                v += *p;
            }

            row[i] = 1;
        }

        return r;
    }
};
