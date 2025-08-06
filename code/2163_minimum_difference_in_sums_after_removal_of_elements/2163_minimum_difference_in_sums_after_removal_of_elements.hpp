#pragma once

#include <algorithm>
#include <bit>
#include <vector>

#include "force_inline.hpp"
#include "hot_path.hpp"
#include "int_if.hpp"
#include "integral_aliases.hpp"
#include "reinterpret_range.hpp"

namespace all_branches
{

template <typename Word, u32 num_words>
class RecursiveBitsetLayer
{
public:
    FORCE_INLINE constexpr void Fill(bool value) noexcept
    {
        std::ranges::fill(
            words,
            value ? std::numeric_limits<u64>::max() : u64{0});
    }

    // Returns word index and
    // boolean which will be true if word became non-zero
    FORCE_INLINE HOT_PATH constexpr std::pair<u32, bool> SetBitExtra(
        u32 index) noexcept
    {
        if constexpr (num_words == 1)
        {
            bool was_zero = words[0] == 0;
            SetBit(index);
            return {0, was_zero};
        }
        else
        {
            u32 word_index = index / 64;
            bool was_zero = words[word_index] == 0;
            SetBit(index);
            return {word_index, was_zero};
        }
    }

    FORCE_INLINE HOT_PATH constexpr void SetBit(u32 index)
    {
        if constexpr (num_words == 1)
        {
            words[0] |= (u64{1} << index);
        }
        else
        {
            words[index / 64] |= (u64{1} << (index % 64));
        }
    }

    // Returns word index and
    // boolean which will be true if word became zero
    FORCE_INLINE HOT_PATH constexpr std::pair<u32, bool> ClearBitExtra(
        u32 index) noexcept
    {
        ClearBit(index);
        if constexpr (num_words == 1)
        {
            return {0, !words[0]};
        }
        else
        {
            u32 word_index = index / 64;
            return {word_index, !words[word_index]};
        }
    }

    FORCE_INLINE HOT_PATH constexpr void ClearBit(u32 index) noexcept
    {
        if constexpr (num_words == 1)
        {
            words[0] &= (~(u64{1} << index));
        }
        else
        {
            words[index / 64] &= (~(u64{1} << (index % 64)));
        }
    }

    std::array<u64, num_words> words{};
};

class Lookup
{
public:
    FORCE_INLINE constexpr void Clear() noexcept
    {
        std::ranges::fill(freq, 0);
        bs0.Fill(false);
        bs1.Fill(false);
        bs2.Fill(false);
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2.words[0]));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1.words[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0.words[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2.words[0]));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1.words[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0.words[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE HOT_PATH constexpr void Add(u32 value) noexcept
    {
        if (freq[value]++ == 0)
        {
            if (auto [wi0, c0] = bs0.SetBitExtra(value); c0)
            {
                if (auto [wi1, c1] = bs1.SetBitExtra(wi0); c1)
                {
                    bs2.SetBit(wi1);
                    // bs2.words[0] |= (u64{1} << wi1);
                }
            }
        }
    }

    FORCE_INLINE HOT_PATH constexpr void Remove(u32 value) noexcept
    {
        if (--freq[value] == 0)
        {
            if (auto [wi0, c0] = bs0.ClearBitExtra(value); c0)
            {
                if (auto [wi1, c1] = bs1.ClearBitExtra(wi0); c1)
                {
                    bs2.ClearBit(wi1);
                    // bs2.words[0] &= ~(u64{1} << wi1);
                }
            }
        }
    }

    std::array<u32, 100'001> freq{};
    RecursiveBitsetLayer<u64, 1563> bs0;
    RecursiveBitsetLayer<u64, 25> bs1;
    RecursiveBitsetLayer<u64, 1> bs2;
};

class Solution
{
public:
    inline static Lookup lookup{};
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT

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
        lookup.Clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Max();
            lookup.Remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        lookup.Clear();
        sum = 0;
        for (u32 v : right)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Min();
            lookup.Remove(v);
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

}  // namespace all_branches

namespace two_branches
{

class Lookup
{
public:
    FORCE_INLINE constexpr void Clear() noexcept
    {
        std::ranges::fill(freq, 0);
        std::ranges::fill(bs0, 0);
        std::ranges::fill(bs1, 0);
        bs2 = 0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE HOT_PATH constexpr void Add(u32 value) noexcept
    {
        if (freq[value]++ == 0)
        {
            const u32 wi0 = value / 64, bi0 = value % 64;
            u64& w0 = bs0[wi0];
            const u64 m0 = u64{1} << bi0;
            // sequence of 64 values becomes non empty: propagate further
            if (std::exchange(w0, w0 | m0) == 0)
            {
                const u32 wi1 = wi0 / 64;
                bs1[wi1] |= u64{1} << (wi0 % 64);
                bs2 |= (u64{1} << (wi1 % 64));
            }
        }
    }

    FORCE_INLINE HOT_PATH constexpr void Remove(u32 value) noexcept
    {
        if (--freq[value] == 0)
        {
            const u32 wi0 = value / 64;
            if (!(bs0[wi0] &= ~(u64{1} << (value % 64))))
            {
                const u32 wi1 = wi0 / 64;
                u64& w1 = bs1[wi1];
                w1 &= ~(u64{1} << (wi0 % 64));
                bs2 &= ~(u64{!w1} << (wi1 % 64));
            }
        }
    }

    std::array<u32, 100'001> freq{};
    std::array<u64, 1563> bs0{};
    std::array<u64, 25> bs1{};
    u64 bs2{};
};

class Solution
{
public:
    inline static Lookup lookup{};
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT

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
        lookup.Clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Max();
            lookup.Remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        lookup.Clear();
        sum = 0;
        for (u32 v : right)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Min();
            lookup.Remove(v);
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

}  // namespace two_branches

namespace one_branch
{

class Lookup
{
public:
    FORCE_INLINE constexpr void Clear() noexcept
    {
        std::ranges::fill(freq, 0);
        std::ranges::fill(bs0, 0);
        std::ranges::fill(bs1, 0);
        bs2 = 0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE HOT_PATH constexpr void Add(u32 value) noexcept
    {
        if (freq[value]++ == 0)
        {
            const u32 wi0 = value / 64;
            bs0[wi0] |= u64{1} << (value % 64);
            const u32 wi1 = wi0 / 64;
            bs1[wi1] |= u64{1} << (wi0 % 64);
            bs2 |= (u64{1} << (wi1 % 64));
        }
    }

    FORCE_INLINE HOT_PATH constexpr void Remove(u32 value) noexcept
    {
        if (--freq[value] == 0)
        {
            const u32 wi0 = value / 64;
            u64& w0 = bs0[wi0];
            w0 &= ~(u64{!freq[value]} << (value % 64));
            const u32 wi1 = wi0 / 64;
            u64& w1 = bs1[wi1];
            w1 &= ~(u64{!w0} << (wi0 % 64));
            bs2 &= ~(u64{!w1} << (wi1 % 64));
        }
    }

    std::array<u32, 100'001> freq{};
    std::array<u64, 1563> bs0{};
    std::array<u64, 25> bs1{};
    u64 bs2{};
};

class Solution
{
public:
    inline static Lookup lookup{};
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT

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
        lookup.Clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Max();
            lookup.Remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        lookup.Clear();
        sum = 0;
        for (u32 v : right)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Min();
            lookup.Remove(v);
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

}  // namespace one_branch

namespace branchless
{

class Lookup
{
public:
    FORCE_INLINE HOT_PATH constexpr void Clear() noexcept
    {
        std::ranges::fill(freq, 0);
        std::ranges::fill(bs0, 0);
        std::ranges::fill(bs1, 0);
        bs2 = 0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE HOT_PATH constexpr void Add(u32 value) noexcept
    {
        freq[value]++;
        const u32 wi0 = value / 64;
        bs0[wi0] |= u64{1} << (value % 64);
        const u32 wi1 = wi0 / 64;
        bs1[wi1] |= u64{1} << (wi0 % 64);
        bs2 |= (u64{1} << (wi1 % 64));
    }

    FORCE_INLINE HOT_PATH constexpr void Remove(u32 value) noexcept
    {
        --freq[value];
        const u32 wi0 = value / 64;
        u64& w0 = bs0[wi0];
        w0 &= ~(u64{!freq[value]} << (value % 64));
        const u32 wi1 = wi0 / 64;
        u64& w1 = bs1[wi1];
        w1 &= ~(u64{!w0} << (wi0 % 64));
        bs2 &= ~(u64{!w1} << (wi1 % 64));
    }

    std::array<u32, 100'001> freq{};
    std::array<u64, 1563> bs0{};
    std::array<u64, 25> bs1{};
    u64 bs2{};
};

class Solution
{
public:
    inline static Lookup lookup{};
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT

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
        lookup.Clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Max();
            lookup.Remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        lookup.Clear();
        sum = 0;
        for (u32 v : right)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Min();
            lookup.Remove(v);
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

}  // namespace branchless

namespace lazy_clear
{

class Lookup
{
public:
    FORCE_INLINE constexpr void Clear() noexcept
    {
        // std::ranges::fill(freq, 0);
        std::ranges::fill(bs0, 0);
        std::ranges::fill(bs1, 0);
        bs2 = 0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE HOT_PATH constexpr void Add(u32 value) noexcept
    {
        const u32 wi0 = value / 64;
        u64& w0 = bs0[wi0];
        const u64 m0 = u64{1} << (value % 64);
        freq[value] = iif(w0 & m0, freq[value], u32{0}) + 1;
        const u32 wi1 = wi0 / 64;
        bs1[wi1] |= u64{std::exchange(w0, w0 | m0) == 0} << (wi0 % 64);
        bs2 |= (u64{1} << (wi1 % 64));
    }

    FORCE_INLINE HOT_PATH constexpr void Remove(u32 value) noexcept
    {
        if (--freq[value] == 0)
        {
            const u32 wi0 = value / 64;
            if (!(bs0[wi0] &= ~(u64{1} << (value % 64))))
            {
                const u32 wi1 = wi0 / 64;
                u64& w1 = bs1[wi1];
                w1 &= ~(u64{1} << (wi0 % 64));
                bs2 &= ~(u64{!w1} << (wi1 % 64));
            }
        }
    }

    std::array<u32, 100'001> freq{};
    std::array<u64, 1563> bs0{};
    std::array<u64, 25> bs1{};
    u64 bs2{};
};

class Solution
{
public:
    inline static Lookup lookup{};
    inline static std::array<i64, 100'001> left_sums_arr;   // NOLINT
    inline static std::array<i64, 100'001> right_sums_arr;  // NOLINT

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
        lookup.Clear();
        i64 sum = 0;
        for (u32 v : left)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        left_sums[0] = sum;
        for (u32 i = 0; i != k; ++i)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Max();
            lookup.Remove(v);
            sum -= v;
            left_sums[i + 1] = sum;
        }

        // Init suffix sum
        lookup.Clear();
        sum = 0;
        for (u32 v : right)
        {
            lookup.Add(v);
            sum += i64{v};
        }

        right_sums.back() = sum;
        for (u32 i = k; i--;)
        {
            u32 v = mid[i];
            lookup.Add(v);
            sum += v;
            v = lookup.Min();
            lookup.Remove(v);
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

}  // namespace lazy_clear
