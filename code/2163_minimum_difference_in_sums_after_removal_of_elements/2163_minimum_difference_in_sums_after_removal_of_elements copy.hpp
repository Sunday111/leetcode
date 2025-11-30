#include <algorithm>
#include <span>
#include <vector>

#include "bitset_priority_queue.hpp"
#include "reinterpret_range.hpp"

class Solution
{
public:
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT
    inline static BitsetPriorityQueue<100'000, 100'000> q{};

    [[nodiscard]] static constexpr i64 minimumDifference(
        std::span<const u32> nums) noexcept
    {
        auto n = static_cast<u32>(nums.size());
        auto k = n / 3;

        auto left = nums.first(k);
        auto mid = nums.subspan(k, k);
        auto right = nums.last(k);

        auto left_sums = std::span{left_sums_arr}.first(k + 1);
        auto right_sums = std::span{right_sums_arr}.first(k + 1);

        // Init prefix sum
        q.clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            q.add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            q.add(v);
            sum += v;
            v = q.max();
            q.remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        q.clear();
        sum = 0;
        for (u32 v : right)
        {
            q.add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            q.add(v);
            sum += v;
            v = q.min();
            q.remove(v);
            sum -= v;
            right_sums[i] = sum;
        }

        // Find min diff
        i64 min_sum = std::numeric_limits<i64>::max();
        for (u32 i = 0; i <= k; ++i)
        {
            min_sum = std::min(left_sums[i] - right_sums[i], min_sum);
        }

        return min_sum;
    }

    [[nodiscard]] FORCE_INLINE static i64 minimumDifference(
        std::vector<int>& nums) noexcept
    {
        return minimumDifference(reinterpret_range<const u32>(nums));
    }
};
