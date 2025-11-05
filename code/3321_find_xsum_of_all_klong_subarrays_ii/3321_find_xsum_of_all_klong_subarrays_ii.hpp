#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

#include "bump_hash_map.hpp"
#include "bump_set.hpp"
#include "reinterpret_range.hpp"

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    std::vector<long long> findXSum(std::span<const u32> nums, u32 k, u32 x)
    {
        SolutionStorage::Instance().Reset();
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> val_to_freq;
        ObjectWithoutDtor<BumpSet<std::pair<u32, u32>, SolutionStorage>>
            freq_val_set;
        ObjectWithoutDtor<BumpSet<std::pair<u32, u32>, SolutionStorage>>
            waitlist;
        u64 current_sum = 0;

        auto add_value = [&](u32 value)
        {
            u32& freq = val_to_freq.get()[value];

            if (freq)
            {
                if (freq_val_set->erase(std::pair{freq, value}))
                {
                    current_sum -= u64{value} * u64{freq};
                }
                else
                {
                    waitlist->erase(std::pair{freq, value});
                }
            }

            if (++freq)
            {
                waitlist->emplace(std::pair{freq, value});
            }
        };

        auto remove_value = [&](u32 value)
        {
            u32& freq = val_to_freq.get()[value];
            if (freq_val_set->erase(std::pair{freq, value}))
            {
                current_sum -= u64{value} * u64{freq};
            }
            else
            {
                waitlist->erase(std::pair{freq, value});
            }

            if (--freq)
            {
                waitlist->emplace(std::pair{freq, value});
            }
        };

        auto refresh_map_size = [&]()
        {
            while (!waitlist->empty() &&
                   (freq_val_set->size() < x ||
                    *waitlist->rbegin() > *freq_val_set->begin()))
            {
                current_sum += u64{waitlist->rbegin()->first} *
                               u64{waitlist->rbegin()->second};
                freq_val_set->insert(
                    waitlist->extract(std::prev(waitlist->end())));
            }

            while (freq_val_set->size() > x)
            {
                auto it = freq_val_set->begin();
                current_sum -= u64{it->second} * u64{it->first};
                waitlist->insert(freq_val_set->extract(it));
            }
        };

        for (u32 i = 0; i != k; ++i) add_value(nums[i]);

        const u32 n = static_cast<u32>(nums.size());
        refresh_map_size();
        std::vector<long long> r;
        r.reserve(n - k + 1);
        r.push_back(static_cast<i64>(current_sum));
        for (u32 i = 0, j = k; j != n; ++i, ++j)
        {
            if (nums[i] != nums[j])
            {
                remove_value(nums[i]);
                add_value(nums[j]);
                refresh_map_size();
            }
            r.push_back(static_cast<i64>(current_sum));
        }

        return r;
    }

    std::vector<long long> findXSum(std::vector<int>& nums, u32 k, u32 x)
    {
        return findXSum(reinterpret_range<u32>(nums), k, x);
    }
};
