#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int findLucky(
        const std::vector<int>& arr) noexcept
    {
        std::array<int, 501> freq{};
        for (auto v : arr) ++freq[v & 0xFFFF];
        int r{-1};
        for (int v = 1; v != 501; ++v)
        {
            if (freq[v & 0xFFFF] == v) r = v;
        }
        return r;
    }
};
