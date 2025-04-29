#pragma once

#include <algorithm>
#include <string_view>
#include <vector>

class Solution
{
public:
    inline static constexpr uint32_t kInvalidIndex =
        std::numeric_limits<uint32_t>::max();

    struct NodeInfo
    {
        uint32_t sibling = kInvalidIndex;
        uint32_t child = kInvalidIndex;
    };

    inline static constexpr size_t root = 0;
    uint32_t n;
    std::vector<NodeInfo> nodes;
    int max_len = 0;
    std::string_view chars;

    int dfs(uint32_t i)
    {
        const char node_char = chars[i];
        int max_a = 0, max_b = 0;

        for (auto child = nodes[i].child; child != kInvalidIndex;
             child = nodes[child].sibling)
        {
            int child_dfs = dfs(child);

            if (child_dfs > max_b && node_char != chars[child])
            {
                max_b = child_dfs;
                if (max_b > max_a)
                {
                    std::swap(max_a, max_b);
                }
            }
        }

        if (int s = max_a + max_b + 1; s > max_len)
        {
            max_len = s;
        }

        return max_a + 1;
    }

    int longestPath(std::vector<int>& parents, std::string_view s)
    {
        max_len = 1;
        chars = s;
        n = static_cast<uint32_t>(parents.size());
        nodes.clear();
        nodes.resize(n);

        for (uint32_t i = 1; i != n; ++i)
        {
            const auto parent = std::bit_cast<uint32_t>(parents[i]);
            const uint32_t sibling = std::exchange(nodes[parent].child, i);
            if (sibling != kInvalidIndex) nodes[i].sibling = sibling;
        }

        dfs(0);

        return max_len;
    }
};
