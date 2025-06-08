#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    std::vector<int> o;
    u32 n;

    constexpr void dfs(u32 prefix) noexcept
    {
        u32 end = prefix + 10;
        for (u32 v = prefix; v != end; ++v)
        {
            if (v <= n)
            {
                o.push_back(std::bit_cast<int>(v));
                dfs(v * 10);
            }
        }
    }

    [[nodiscard]] constexpr std::vector<int> lexicalOrder(u32 n_) noexcept
    {
        n = n_;
        o.reserve(n_);

        for (u32 v = 1; v != 10; ++v)
        {
            if (v <= n)
            {
                o.push_back(std::bit_cast<int>(v));
                dfs(v * 10);
            }
        }

        return std::move(o);
    }
};
