#pragma once

#include <algorithm>
#include <bit>
#include <cstring>
#include <iostream>
#include <vector>

#include "3041_distinct_dp.hpp"
#include "cast/cast.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"

class LC_SOLUTION_NAME(_flat_bitset)
{
    static constexpr u32 kWords = (1'000'001 + 63) / 64;
    inline static u64 present[kWords];
    inline static u64 duplicate[kWords];

    static void add_occurrence(u32 x)
    {
        u32 word = x >> 6;
        u64 mask = u64{1} << (x & 63);
        if (duplicate[word] & mask) return;
        duplicate[word] |= present[word] & mask;
        present[word] |= mask;
    }

    static void for_each_distinct_descending(u32 first, u32 last, auto&& visit)
    {
        for (u32 i = last + 1; i-- != first;)
        {
            u64 word = present[i];
            while (word)
            {
                u32 bit = 63 - cast<u32>(std::countl_zero(word));
                u64 mask = u64{1} << bit;
                word ^= mask;
                visit((i << 6) | bit, (duplicate[i] & mask) != 0);
            }
        }
    }

public:
    [[gnu::flatten, gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]]
    static u32 maxSelectedElements(std::vector<int>& nums) noexcept
    {
        const auto* data = reinterpret_cast<const u32*>(nums.data());
        u32 n = cast<u32>(nums.size());
        u32 low = 1'000'000, high = 0;
        for (u32 i = 0; i != n; ++i)
        {
            low = std::min(low, data[i]);
            high = std::max(high, data[i]);
        }
        u32 first = low >> 6, last = high >> 6;
        std::memset(present + first, 0, (last - first + 1) * 8);
        std::memset(duplicate + first, 0, (last - first + 1) * 8);
        for (u32 i = 0; i != n; ++i) add_occurrence(data[i]);

        lc3041::DistinctDP dp;
        for_each_distinct_descending(
            first,
            last,
            [&](u32 x, bool repeated) { dp.add(x, repeated); });
        return dp.answer;
    }
};
