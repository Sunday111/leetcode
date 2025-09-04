#pragma once

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int score(
        const std::vector<int>& row) noexcept
    {
        return std::accumulate(row.begin(), row.end(), 0);
    }

    [[nodiscard]] static constexpr std::vector<int> kWeakestRows(
        const std::vector<std::vector<int>>& mat,
        size_t k)
    {
        std::array<int, 100> scores;  // NOLINT
        std::ranges::copy(mat | std::views::transform(score), scores.begin());
        std::vector<int> indices = std::ranges::to<std::vector>(
            std::views::iota(0, static_cast<int>(mat.size())));
        std::ranges::sort(
            indices,
            [&](int a, int b)
            {
                int sa = scores[a & 0xFF], sb = scores[b & 0xFF];
                return sa < sb || (sa == sb && a < b);
            });

        indices.resize(k);
        return indices;
    }
};
