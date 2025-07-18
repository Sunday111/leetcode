#include <algorithm>
#include <bit>
#include <cstdint>
#include <force_inline.hpp>
#include <span>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

namespace all_branches
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

    [[nodiscard]] FORCE_INLINE constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE constexpr void Add(u32 value) noexcept
    {
        if (freq[value]++ == 0)
        {
            const u32 wi0 = value / 64, bi0 = value % 64;
            u64& w0 = bs0[wi0];
            const u64 m0 = u64{1} << bi0;
            // sequence of 64 values becomes non empty: propagate further
            if (std::exchange(w0, w0 | m0) == 0)
            {
                const u32 wi1 = wi0 / 64, bi1 = wi0 % 64;
                u64& w1 = bs1[wi1];
                const u64 m1 = u64{1} << bi1;
                // block of 4096 values becomes non empty: propagate further
                if (std::exchange(w1, w1 | m1) == 0)
                {
                    bs2 |= (u64{1} << (wi1 % 64));
                }
            }
        }
    }

    FORCE_INLINE constexpr void Remove(u32 value) noexcept
    {
        if (--freq[value] == 0)
        {
            const u32 wi0 = value / 64, bi0 = value % 64;
            u64& w0 = bs0[wi0];
            w0 &= ~(u64{1} << bi0);
            // sequence of 64 values becomes empty: propagate further
            if (w0 == 0)
            {
                const u32 wi1 = wi0 / 64, bi1 = wi0 % 64;
                u64& w1 = bs1[wi1];
                w1 &= ~(u64{1} << bi1);
                // block of 4096 values becomes empty: propagate further
                if (w1 == 0)
                {
                    bs2 &= ~(u64{1} << (wi1 % 64));
                }
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

    [[nodiscard]] FORCE_INLINE constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE constexpr void Add(u32 value) noexcept
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

    FORCE_INLINE constexpr void Remove(u32 value) noexcept
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

    [[nodiscard]] FORCE_INLINE constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE constexpr void Add(u32 value) noexcept
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

    FORCE_INLINE constexpr void Remove(u32 value) noexcept
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
    FORCE_INLINE constexpr void Clear() noexcept
    {
        std::ranges::fill(freq, 0);
        std::ranges::fill(bs0, 0);
        std::ranges::fill(bs1, 0);
        bs2 = 0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 Min() const noexcept
    {
        u32 wi1 = static_cast<u32>(std::countr_zero(bs2));
        u32 bi1 = static_cast<u32>(std::countr_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(std::countr_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 Max() const noexcept
    {
        u32 wi1 = static_cast<u32>(63 - std::countl_zero(bs2));
        u32 bi1 = static_cast<u32>(63 - std::countl_zero(bs1[wi1]));
        u32 wi0 = wi1 * 64 + bi1;
        u32 bi0 = static_cast<u32>(63 - std::countl_zero(bs0[wi0]));
        return wi0 * 64 + bi0;
    }

    FORCE_INLINE constexpr void Add(u32 value) noexcept
    {
        freq[value]++;
        const u32 wi0 = value / 64;
        bs0[wi0] |= u64{1} << (value % 64);
        const u32 wi1 = wi0 / 64;
        bs1[wi1] |= u64{1} << (wi0 % 64);
        bs2 |= (u64{1} << (wi1 % 64));
    }

    FORCE_INLINE constexpr void Remove(u32 value) noexcept
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
