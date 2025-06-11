#pragma once

#include <cassert>
#include <cmath>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] static constexpr u64
    maxProgressionLength(u64 first, u64 step, u64 sum) noexcept
    {
        const double t =
            static_cast<double>(2 * first) - static_cast<double>(step);
        const double numerator =
            std::sqrt(t * t + static_cast<double>(8 * step * sum)) - t;
        return static_cast<u64>(
            std::max(0.0, numerator / static_cast<double>(2 * step)));
    }

    [[nodiscard]] static constexpr u64
    progressionSum(u64 first, u64 length, u64 step) noexcept
    {
        if (length == 0) return 0;
        return ((first + first + (length - 1) * step) * length) / 2;
    }

    [[nodiscard]] static constexpr std::vector<int> memLeak(u64 m1, u64 m2)
    {
        u64 next = 1;

        {
            auto *high = &m1, *low = &m2;
            if (m2 > m1) std::swap(high, low);
            auto diff = *high - *low;
            if (auto len = maxProgressionLength(next, 1, diff))
            {
                auto sum = progressionSum(next, len, 1);
                *high -= sum;
                next += len;
            }
        }

        if (m2 > m1 && m2 >= next) m2 -= next++;

        if (m1 >= m2)
        {
            if (auto l = std::min(
                    maxProgressionLength(next, 2, m1),
                    maxProgressionLength(next + 1, 2, m2)))
            {
                m1 -= progressionSum(next, l, 2);
                m2 -= progressionSum(next + 1, l, 2);
                next += 2 * l;
            }

            if (auto l = maxProgressionLength(next, 1, m1))
            {
                auto sum = progressionSum(next, l, 1);
                m1 -= sum;
                next += l;
            }
        }

        return {
            static_cast<int>(next),
            static_cast<int>(m1),
            static_cast<int>(m2)};
    }
};
