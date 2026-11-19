#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(
        std::vector<int>& nums,
        const int target)
    {
        std::ranges::sort(nums);

        std::vector<std::vector<int>> results;
        if (nums.size() < 4) return results;

        const auto end = nums.end();
        auto i_end = end - 3;
        auto j_end = end - 2;
        auto k_begin = end - 1;

        for (auto i = nums.begin(); i != i_end;
             i = std::upper_bound(i, i_end, *i))
        {
            const int64_t iv = *i;

            if (iv + 3 * int64_t{*(i + 1)} > target)
            {
                break;
            }

            if (3 * int64_t{*k_begin} + iv < target)
            {
                continue;
            }

            for (auto j = std::next(i); j != j_end;
                 j = std::upper_bound(j, j_end, *j))
            {
                auto k_end = j + 1;
                auto k = k_begin;

                if ((iv + 3 * int64_t{*j} > target) ||
                    (3 * int64_t{*k_begin} + iv < target))
                {
                    break;
                }

                const int64_t break_cond = int64_t{target - *j} - iv;

                while (k != k_end)
                {
                    int64_t kv{*k};
                    int64_t s3 = iv + int64_t{*j} + kv;
                    int64_t search_val = target - s3;

                    if (2 * int64_t{*k} < break_cond) break;

                    if (std::binary_search(k_end, k, search_val))
                    {
                        results.push_back(
                            {static_cast<int>(iv),
                             *j,
                             *k,
                             static_cast<int>(search_val)});
                    }

                    int pk = *k;
                    do
                    {
                        --k;
                    } while (k != k_end && *k == pk);
                }
            }
        }

        return results;
    }
};
