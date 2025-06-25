#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using i32 = int32_t;
using i64 = int64_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard]] static constexpr i64 kthSmallestProduct(
        const std::vector<i32>& nums1,
        const std::vector<i32>& nums2,
        u64 k) noexcept
    {
        auto count_products_less_eq_than = [&](i64 x)
        {
            auto i = nums1.begin();

            u64 total = 0;
            while (i != nums1.end() && *i < 0)
            {
                const i64 v = *i;

                auto j = i;
                while (i != nums1.end() && *i == v) ++i;

                // Sequence of products is descending
                auto it = std::ranges::upper_bound(
                    nums2,
                    x,
                    std::greater{},
                    [&](int v2) { return i64{v2} * v; });

                auto cnt1 = static_cast<u64>(std::distance(j, i));
                u64 cnt2 = static_cast<u64>(std::distance(it, nums2.end()));

                total += cnt1 * cnt2;
            }

            if (i != nums1.end() && *i == 0)
            {
                auto j = i;
                while (i != nums1.end() && *i == 0) ++i;
                u64 cnt1 = static_cast<u64>(std::distance(j, i));
                u64 cnt2 = x > 0 ? nums2.size() : 0;
                total += cnt1 * cnt2;
            }

            while (i != nums1.end())
            {
                i64 v = *i;

                auto j = i;
                while (i != nums1.end() && *i == v) ++i;

                // Sequence of products is ascending
                auto it = std::ranges::lower_bound(
                    nums2,
                    x,
                    std::less{},
                    [&](int v2) { return i64{v2} * v; });

                auto cnt1 = static_cast<u64>(std::distance(j, i));
                u64 cnt2 = static_cast<u64>(std::distance(nums2.begin(), it));

                total += cnt1 * cnt2;
            }

            return total;
        };

        const i64 min_a = nums1.front();
        const i64 max_a = nums1.back();
        const i64 min_b = nums2.front();
        const i64 max_b = nums2.back();
        const i64 min_product = std::min(
            {min_a * min_b, min_a * max_b, max_a * min_b, max_a * max_b});
        const i64 max_product = std::max(
            {min_a * min_b, min_a * max_b, max_a * min_b, max_a * max_b});

        // Binary search by answer
        return *std::ranges::upper_bound(
                   std::views::iota(min_product, max_product + 1),
                   k - 1,
                   std::less{},
                   count_products_less_eq_than) -
               1;
    }
};
