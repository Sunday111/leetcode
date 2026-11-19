#pragma once

#include <iostream>
#include <vector>

#include "3041_distinct_dp.hpp"
#include "cast.hpp"
#include "radix_sorter.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"

class LC_SOLUTION_NAME(radix)
{
public:
    [[gnu::flatten, gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]] u32
    maxSelectedElements(std::vector<int>& nums) noexcept
    {
        auto* data = reinterpret_cast<u32*>(nums.data());
        u32 n = cast<u32>(nums.size());
        radix_sort<10, 2>(data, n);

        lc3041::DistinctDP dp;
        for (u32 i = n; i != 0;)
        {
            u32 end = i;
            u32 x = data[--i];
            while (i != 0 && data[i - 1] == x) --i;
            dp.add(x, end - i > 1);
        }
        return dp.answer;
    }
};
