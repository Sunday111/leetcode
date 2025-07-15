#pragma once

#include <array>
#include <span>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

template <typename To, typename From, size_t extent = std::dynamic_extent>
[[nodiscard]] ATTR static auto reinterpret_span(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
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
    ATTR static void do_pass(std::span<UT> arr) noexcept
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
            // Compute descending start positions directly
            UT sum = 0;
            for (u32 i = base; i--;)
            {
                auto c = count[i];
                count[i] = sum;
                sum += c;
            }

            // Stable placement
            for (u32 i = 0; i != n; ++i)
            {
                UT digit = (arr[i] >> shift) & mask;
                temp[count[digit]++] = post_flip ? arr[i] ^ sign_mask : arr[i];
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes pass for each do_pass index.
    template <u8... pass_index>
    ATTR static void do_passes(
        std::span<UT> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    ATTR static void sort(std::span<T> arr) noexcept
    {
        if (arr.size()) do_passes(reinterpret_span<UT>(arr), pass_idx_seq);
    }
};

class Solution
{
public:
    [[nodiscard]] static constexpr int longestConsecutive(
        std::vector<int>& nums) noexcept
    {
        RadixSorter<int, SortOrder::Ascending, 8>::sort(nums);

        if (nums.empty()) return 0;

        int max_len = 1;
        int len = 1;
        int prev = nums.front();

        const u32 n = static_cast<u32>(nums.size());
        for (u32 i = 1; i != n; ++i)
        {
            auto v = nums[i];
            len = v > (prev + 1) ? 1 : len + (v - prev);
            prev = v;
            max_len = std::max(max_len, len);
        }

        return max_len;
    }
};
