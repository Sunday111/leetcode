#pragma once

#include <span>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int maximumLength(
        const std::vector<int>& nums) noexcept
    {
        int alt = 1, o = nums.front() & 1, e = !o, f = e;
        for (int v : std::span{nums}.subspan(1))
        {
            int t = v & 1;
            alt += t == f;
            f = (f + (t == f)) & 1;
            ++*(t ? &o : &e);
        }

        return std::max({e, o, alt});
    }
};
