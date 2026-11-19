#include <reinterpret_range.hpp>
#include <span>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
    u32 target{};
    std::vector<u32> curr;
    std::vector<std::vector<u32>> r;
    std::span<const std::vector<u32>> g;

    constexpr void dfs(u32 i) noexcept
    {
        curr.push_back(i);

        if (i == target)
        {
            r.push_back(curr);
        }
        else
        {
            for (u32 j : g[i]) dfs(j);
        }

        curr.pop_back();
    }

public:
    [[nodiscard]] constexpr std::vector<std::vector<int>> allPathsSourceTarget(
        const std::vector<std::vector<int>>& graph) noexcept
    {
        target = static_cast<u32>(graph.size() - 1);
        g = reinterpret_cast<const std::vector<std::vector<u32>>&>(graph);
        dfs(0);
        return std::move(reinterpret_cast<std::vector<std::vector<int>>&>(r));
    }
};
