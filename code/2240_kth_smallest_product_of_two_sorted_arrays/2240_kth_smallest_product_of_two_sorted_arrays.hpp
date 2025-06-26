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
        auto zero_begin_1 = std::ranges::lower_bound(nums1, 0);
        auto zero_end_1 = std::ranges::upper_bound(nums1, 0);
        auto zero_begin_2 = std::ranges::lower_bound(nums2, 0);
        auto zero_end_2 = std::ranges::upper_bound(nums2, 0);
        u64 num_zeroes_1 =
            static_cast<u64>(std::distance(zero_begin_1, zero_end_1));

        [[maybe_unused]] const u64 num_positive_1 =
            static_cast<u64>(nums1.end() - zero_end_1);
        [[maybe_unused]] const u64 num_positive_2 =
            static_cast<u64>(nums2.end() - zero_end_2);
        [[maybe_unused]] const u64 num_negative_1 =
            static_cast<u64>(zero_begin_1 - nums1.begin());
        [[maybe_unused]] const u64 num_negative_2 =
            static_cast<u64>(zero_begin_2 - nums2.begin());

        auto count_products_less_eq_than = [&](i64 x)
        {
            auto i = nums1.begin();

            u64 total = 0;

            if (x < 0)
            {
                auto start = zero_end_2;
                while (i != zero_begin_1 && start != nums2.end())
                {
                    // v < 0, x < 0
                    const i64 v = *i;

                    auto j = i;
                    while (i != nums1.end() && *i == v) ++i;

                    // Sequence of products is descending
                    i64 limit = x / v;
                    while (start != nums2.end() && i64{*start} <= limit)
                    {
                        ++start;
                    }

                    auto cnt1 = static_cast<u64>(std::distance(j, i));
                    u64 cnt2 =
                        static_cast<u64>(std::distance(start, nums2.end()));

                    total += cnt1 * cnt2;
                }

                i = zero_begin_1;
            }
            else
            {
                // v < 0, x >= 0
                // Need to make negative numbers from negative numbers
                // Any positive v2 is good
                total += num_negative_1 * num_positive_2;

                if (x > 0 && (nums2.size() - num_positive_2))
                {
                    auto start_2 = zero_end_2 - 1;
                    auto end_2 = nums2.begin() - 1;
                    while (i != zero_begin_1 && start_2 != end_2)
                    {
                        const i64 v = *i;

                        auto j = i;
                        while (i != nums1.end() && *i == v) ++i;

                        // Sequence of products is descending
                        while (start_2 != end_2 && i64{*start_2} * v < x)
                        {
                            --start_2;
                        }

                        auto cnt1 = static_cast<u64>(std::distance(j, i));
                        u64 cnt2 = static_cast<u64>(
                                       std::distance(start_2, zero_end_2)) -
                                   1;

                        total += cnt1 * cnt2;
                    }

                    auto cnt1 =
                        static_cast<u64>(std::distance(i, zero_begin_1));
                    u64 cnt2 =
                        static_cast<u64>(std::distance(start_2, zero_end_2)) -
                        1;
                    total += cnt1 * cnt2;
                    i = zero_begin_1;
                }
            }

            if (i != zero_end_1)
            {
                i = zero_end_1;
                if (x > 0) total += num_zeroes_1 * nums2.size();
            }

            if (x < 0)
            {
                // V > 0; x < 0: consider only negative from nums 2
                auto start_2 = nums2.begin();
                while (i != nums1.end() && start_2 != zero_begin_2)
                {
                    i64 v = *i;

                    auto j = i;
                    while (i != nums1.end() && *i == v) ++i;

                    // Sequence of products is ascending
                    while (start_2 != zero_begin_2 && i64{*start_2} * v < x)
                    {
                        ++start_2;
                    }

                    auto cnt1 = static_cast<u64>(std::distance(j, i));
                    u64 cnt2 =
                        static_cast<u64>(std::distance(nums2.begin(), start_2));

                    total += cnt1 * cnt2;
                }
                auto cnt1 = static_cast<u64>(std::distance(i, nums1.end()));
                u64 cnt2 =
                    static_cast<u64>(std::distance(nums2.begin(), start_2));
                total += cnt1 * cnt2;
            }
            else
            {
                // v > 0; x >= 0
                // Any negative v2 is good
                total += num_positive_1 * num_negative_2;

                if (x > 0)
                {
                    // auto start_2 = nums2.end() - 1;
                    // auto end_2 = zero_end_2 - 1;
                    // while (i != nums1.end())
                    // {
                    //     i64 v = *i;

                    //     auto j = i;
                    //     while (i != nums1.end() && *i == v) ++i;

                    //     while (start_2 != end_2 && i64{*start_2} * v > x)
                    //     {
                    //         --start_2;
                    //     }

                    //     auto cnt1 = static_cast<u64>(std::distance(j, i));
                    //     u64 cnt2 = static_cast<u64>(
                    //         std::distance(zero_end_2, start_2));

                    //     total += cnt1 * cnt2;
                    // }

                    auto it = nums2.end();
                    while (i != nums1.end())
                    {
                        i64 v = *i;

                        auto j = i;
                        while (i != nums1.end() && *i == v) ++i;

                        // Sequence of products is ascending
                        it = std::ranges::lower_bound(
                            zero_begin_2,
                            it,
                            x,
                            std::less{},
                            [&](int v2) { return i64{v2} * v; });

                        auto cnt1 = static_cast<u64>(std::distance(j, i));
                        u64 cnt2 =
                            static_cast<u64>(std::distance(zero_begin_2, it));

                        total += cnt1 * cnt2;
                    }
                }
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
