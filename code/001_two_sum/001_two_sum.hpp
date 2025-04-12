#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <span>
#include <vector>

class Solution
{
    template <std::integral T, std::unsigned_integral I, typename F>
    [[nodiscard]] static std::tuple<I, I> twoSumSortedUnsigned(std::vector<I>& indices, F get_value, T target) noexcept
    {
        auto idx_array_lower_bound = [&](const T& value)
        {
            return std::ranges::lower_bound(indices, value, [&](I ia, const T& b) { return get_value(ia) < b; });
        };

        auto idx_array_upper_bound = [&](const T& value)
        {
            return std::ranges::upper_bound(indices, value, [&](const T& a, I ib) { return a < get_value(ib); });
        };

        // Leave only acceptable range of indices
        const T min_value = get_value(indices.front());
        indices.erase(idx_array_upper_bound(target - min_value), indices.end());

        auto iteration_end = idx_array_upper_bound(target - min_value);
        for (auto a_it = idx_array_lower_bound(min_value); a_it != iteration_end; ++a_it)
        {
            const T& value_a = get_value(*a_it);
            const T value_b = target - value_a;

            // check that value b exist
            auto b_it = value_a == value_b ? (a_it + 1) : idx_array_lower_bound(value_b);
            if (b_it != indices.end() && get_value(*b_it) == value_b) return {*a_it, *b_it};
        }

        return {};
    }

public:
    template <std::integral T, size_t extent = std::dynamic_extent>
    [[nodiscard]] static std::vector<T> twoSum(std::span<const T, extent> nums, T target) noexcept
    {
        using Index = uint16_t;  // This is enough as 2 <= nums.length <= 10^4

        // Prepare indices array
        auto indices = std::ranges::to<std::vector>(std::views::iota(Index{0}, static_cast<Index>(nums.size())));

        // projection from index to value
        const auto proj = std::bind_front(&std::span<const T, extent>::operator[], &nums);

        // Sort indices by values that they represent in 'nums' array
        std::ranges::sort(indices, std::less{}, proj);

        const auto [i0, i1] = twoSumSortedUnsigned(indices, proj, target);
        return {static_cast<T>(i0), static_cast<T>(i1)};
    }

    template <std::integral T, typename Allocator>
    [[nodiscard]] static std::vector<T> twoSum(const std::vector<T, Allocator> nums, T target) noexcept
    {
        return twoSum(std::span{nums}, target);
    }
};
