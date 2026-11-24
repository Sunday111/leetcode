#pragma once

#include <iostream>
#include <vector>

#include "3041_distinct_dp.hpp"
#include "cast.hpp"
#include "pyramid_bitset/pbs_add_ex.hpp"
#include "pyramid_bitset/pbs_add_if.hpp"
#include "pyramid_bitset/pbs_get.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_max.hpp"
#include "pyramid_bitset/pbs_prev.hpp"
#include "pyramid_bitset/pbs_required_buffer_words.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"

class LC_SOLUTION_NAME(_pyramid_bitset)
{
    using Bits = PyramidBitset<1'000'001>;
    inline static Bits::WordType
        present[pbs_required_buffer_words<Bits::kCapacity>()];
    inline static Bits::WordType
        duplicate[pbs_required_buffer_words<Bits::kCapacity>()];

public:
    [[gnu::flatten, gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]]
    static u32 maxSelectedElements(std::vector<int>& nums) noexcept
    {
        auto seen = pbs_make<Bits::kCapacity>(present);
        auto repeated = pbs_make<Bits::kCapacity>(duplicate);
        pbs_initialize<false>(seen);
        pbs_initialize<false>(repeated);

        const auto* data = reinterpret_cast<const u32*>(nums.data());
        u32 n = cast<u32>(nums.size());
        for (u32 i = 0; i != n; ++i)
        {
            u32 x = data[i];
            pbs_add_if(repeated, x, !pbs_add_ex(seen, x));
        }

        lc3041::DistinctDP dp;
        for (u32 x = pbs_max(seen); x != Bits::kCapacity;
             x = cast<u32>(pbs_prev(seen, x)))
        {
            dp.add(x, pbs_get(repeated, x));
        }
        return dp.answer;
    }
};
