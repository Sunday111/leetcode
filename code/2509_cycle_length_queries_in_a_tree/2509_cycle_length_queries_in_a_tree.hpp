#pragma once

#include <bit>
#include <vector>

// 32 - countl_zero(node value) -> branch length
class Solution
{
public:
    inline static constexpr uint32_t sharedParent(uint32_t a, uint32_t b)
    {
        {  // Ensure a <= b
            uint32_t m = a < b ? 0 : ~0u;
            uint32_t t = (a ^ b) & m;
            a ^= t;
            b ^= t;
        }

        if (a > 1)
        {
            while (std::countl_zero(a) != std::countl_zero(b))
            {
                b /= 2;
            }

            while (a != b)
            {
                a /= 2;
                b /= 2;
            }
        }

        return a;
    }

    inline static constexpr int cycleLengthQuery(uint32_t a, uint32_t b)
    {
        return 2 * std::countl_zero(sharedParent(a, b)) + 1 -
               std::countl_zero(a) - std::countl_zero(b);
    }

    std::vector<int> cycleLengthQueries(
        [[maybe_unused]] int n,
        const std::vector<std::vector<int>>& queries)
    {
        std::vector<int> results;
        results.reserve(queries.size());
        for (auto& query : queries)
        {
            results.push_back(cycleLengthQuery(
                static_cast<uint32_t>(query[0]),
                static_cast<uint32_t>(query[1])));
        }

        return results;
    }
};
