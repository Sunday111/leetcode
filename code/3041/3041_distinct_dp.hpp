#pragma once

#include <algorithm>

#include "integral_aliases.hpp"

namespace lc3041
{
// Feed distinct values in descending order; only the first two copies matter.
struct DistinctDP
{
    u32 previous = 0, keep = 0, increment = 0, answer = 0;

    void add(u32 x, bool repeated)
    {
        u32 d = previous - x;
        u32 next_keep = 1 + (keep & -u32{d == 1});
        u32 next_increment =
            1 + (increment & -u32{d == 1}) + (keep & -u32{d == 2});
        keep = repeated ? next_increment + 1 : next_keep;
        increment = next_increment;
        previous = x;
        answer = std::max(answer, std::max(keep, increment));
    }
};
}  // namespace lc3041
