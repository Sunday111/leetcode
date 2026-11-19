#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    template <size_t i>
    static constexpr auto get_i = []<typename T>(const T& arg)
    {
        if constexpr (std::same_as<std::vector<int>, T>)
        {
            return arg[i];
        }
        else
        {
            return std::get<i>(arg);
        }
    };

    static constexpr auto get_min = [](const auto& arg)
    {
        return get_i<0>(arg);
    };

    static constexpr auto get_max = [](const auto& arg)
    {
        return get_i<1>(arg);
    };

    static constexpr auto query_less =
        [](const auto& query_a, const auto& query_b)
    {
        if (auto a_min = get_min(query_a), b_min = get_min(query_b);
            a_min == b_min)
        {
            return get_max(query_a) < get_max(query_b);
        }
        else
        {
            return a_min < b_min;
        }
    };

    bool isZeroArray(
        std::vector<int>& nums,
        std::vector<std::vector<int>>& queries)
    {
        std::ranges::sort(queries, query_less);

        size_t i = 0;
        auto sector_begin = queries.begin();
        while (sector_begin != queries.end())
        {
            // All numbers before this query must already be zeroed
            size_t start = static_cast<size_t>(get_min(*sector_begin));
            while (i < start)
            {
                if (nums[i] > 0) return false;
                ++i;
            }

            // Find the next query which starts with a bigger index
            auto sector_end = std::lower_bound(
                sector_begin,
                queries.end(),
                std::make_pair(get_min(*sector_begin) + 1, 0),
                query_less);

            // [sector_begin; sector_end) now describe range of queries
            // with the same first index

            size_t next_sector_begin = nums.size();
            if (sector_end != queries.end())
            {
                next_sector_begin = static_cast<size_t>(get_min(*sector_end));
            }

            while (sector_begin != sector_end)
            {
                size_t end = static_cast<size_t>(get_max(*sector_begin)) + 1;

                const int k =
                    static_cast<int>(std::distance(sector_begin, sector_end));
                const size_t test_end = std::min(next_sector_begin, end);
                while (i != test_end)
                {
                    if (nums[i] > k) return false;
                    ++i;
                }
                start = std::max(start, test_end);
                while (start != end)
                {
                    nums[start++] -= k;
                }

                const auto v1 = get_min(*sector_begin),
                           v2 = get_max(*sector_begin);
                do
                {
                    ++sector_begin;
                } while (sector_begin != sector_end &&
                         v1 == get_min(*sector_begin) &&
                         v2 == get_max(*sector_begin));
            }
        }

        for (; i != nums.size(); ++i)
        {
            if (nums[i] > 0) return false;
        }

        return true;
    }
};
