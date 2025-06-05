#pragma once

#include <algorithm>
#include <queue>
#include <vector>

class Solution
{
public:
    template <size_t i>
    [[nodiscard]] static constexpr uint32_t getI(
        const std::vector<int>& v) noexcept
    {
        return std::bit_cast<uint32_t>(v[i]);
    }

    template <size_t i>
    [[nodiscard]] static constexpr uint32_t getI(
        const std::pair<int, int>& v) noexcept
    {
        return std::bit_cast<uint32_t>(std::get<i>(v));
    }

    template <typename T>
    [[nodiscard]] static constexpr uint32_t getMin(const T& arg) noexcept
    {
        return getI<0>(arg);
    }

    template <typename T>
    [[nodiscard]] static constexpr uint32_t getMax(const T& arg) noexcept
    {
        return getI<1>(arg);
    }

    static constexpr auto queryLess = [](const auto& a, const auto& b)
    {
        const auto min_a = getMin(a);
        const auto min_b = getMin(b);
        if (min_a == min_b) return getMax(a) < getMax(b);
        return min_a < min_b;
    };

    int maxRemoval(
        std::vector<int>& nums,
        std::vector<std::vector<int>>& queries)
    {
        std::ranges::sort(queries, queryLess);

        int decrement = 0;
        uint32_t next_query = 0;
        uint32_t num_applied = 0;
        std::vector<int32_t> diff(nums.size() + 1, 0);
        std::vector<uint32_t> cnt(nums.size(), 0);
        std::priority_queue<size_t> behind_queries;

        const uint32_t n = static_cast<uint32_t>(nums.size());
        for (uint32_t i = 0; i != n; ++i)
        {
            // This index can already be zeroed by already applied ranges
            while (decrement + diff[i] < nums[i])
            {
                for (; next_query != queries.size(); ++next_query)
                {
                    auto& query = queries[next_query];
                    if (getMin(query) > i) break;
                    size_t max_val = static_cast<size_t>(getMax(query));
                    if (++cnt[max_val] == 1) behind_queries.push(max_val);
                }

                if (behind_queries.empty()) return -1;
                if (behind_queries.top() < i) return -1;

                size_t top = behind_queries.top();
                if (--cnt[top] == 0) behind_queries.pop();
                ++num_applied;

                ++decrement;
                diff[top + 1]--;
            }

            decrement += diff[i];
        }

        return static_cast<int>(queries.size() - num_applied);
    }
};
