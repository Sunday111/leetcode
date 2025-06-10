#pragma once

#include <algorithm>
#include <cassert>

class Solution
{
public:
    using u64 = uint64_t;

    [[nodiscard]] static constexpr u64 findKthNumber(u64 n, u64 k) noexcept
    {
        return solve(0, n, k);
    }

    [[nodiscard]] static constexpr u64 solve(u64 current, u64 n, u64 k) noexcept
    {
        if (!k) return current / 10;

        for (u64 i = std::max<u64>(current, 1); i < current + 10; ++i)
        {
            u64 count = numOfChildren(i, i + 1, n);
            if (count >= k) return solve(i * 10, n, k - 1);
            k -= count;
        }
        std::unreachable();
    }

    [[nodiscard]] static constexpr u64
    numOfChildren(u64 current, u64 neighbour, u64 n) noexcept
    {
        if (neighbour > n)
        {
            if (current > n) return 0;
            return n - current + 1;
        }
        return neighbour - current +
               numOfChildren(current * 10, neighbour * 10, n);
    }
};
