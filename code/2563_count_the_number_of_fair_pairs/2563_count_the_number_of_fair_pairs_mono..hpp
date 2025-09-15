#include <algorithm>
#include <array>
#include <cstdint>
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

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;
    static constexpr UT sign_mask = UT{1} << (num_bits - 1);

    inline static std::array<UT, base> count;
    inline static std::array<UT, 100'001> temp;

    template <u8 pass_index>
    FORCE_INLINE static void do_pass(std::span<UT> arr) noexcept
    {
        count.fill(0);
        constexpr UT shift = pass_index * bits_per_pass;

        // Count digit occurrences
        for (auto& v : arr)
        {
            constexpr bool is_first_pass = pass_index == 0;
            if constexpr (std::is_signed_v<T> && is_first_pass) v ^= sign_mask;

            ++count[(v >> shift) & mask];
        }

        const u32 n = static_cast<u32>(arr.size());

        constexpr bool post_flip =
            std::is_signed_v<T> && (pass_index == (num_passes - 1));

        if constexpr (order == SortOrder::Ascending)
        {
            // Prefix sums for positions
            for (u32 i = 1; i != base; ++i) count[i] += count[i - 1];

            // Stable placement
            for (u32 i = n; i--;)
            {
                UT digit = (arr[i] >> shift) & mask;
                temp[--count[digit]] = post_flip ? arr[i] ^ sign_mask : arr[i];
            }
        }
        else
        {
            // Compute descending start positions
            UT sum = 0;
            for (u32 i = base; i--;) sum += std::exchange(count[i], sum);

            // Stable placement
            for (u32 i = 0; i != n; ++i)
            {
                UT digit = (arr[i] >> shift) & mask;
                temp[count[digit]++] = post_flip ? arr[i] ^ sign_mask : arr[i];
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    FORCE_INLINE static void do_passes(
        std::span<UT> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    FORCE_INLINE static void sort(std::span<T> arr) noexcept
    {
        if (arr.size()) do_passes(reinterpret_range<UT>(arr), pass_idx_seq);
    }
};

template <
    std::integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept
{
    RadixSorter<T, order, bits_per_pass, num_passes>::sort(arr);
}

class Solution
{
public:
    [[nodiscard]] static constexpr i64
    countFairPairs(std::vector<i32>& nums, i32 lower, i32 upper) noexcept
    {
        radix_sort<i32, SortOrder::Ascending, 16, 2>(nums);
        std::ranges::sort(nums);

        auto countPairs = [&](i32 bound)
        {
            i64 count = 0;
            auto l = nums.begin(), r = nums.end() - 1;
            while (l < r)
            {
                auto ok = *l + *r <= bound;
                count += ok * (r - l);
                l += ok;
                r -= !ok;
            }
            return count;
        };

        return countPairs(upper) - countPairs(lower - 1);
    }
};
