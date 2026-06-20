#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <span>
#include <utility>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))



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
    bool stable,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass),
    u32 capacity = 100'001>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;

    inline static std::array<UT, base> count;
    inline static std::array<UT, capacity> temp;

    template <u8 pass_index>
    FORCE_INLINE static void do_pass(std::span<UT> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        count.fill(0);
        constexpr UT shift = pass_index * bits_per_pass;
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking = std::is_signed_v<T>;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (num_passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (auto& v : arr)
        {
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        const u32 n = cast<u32>(arr.size());

        if constexpr (order == SortOrder::Ascending)
        {
            if constexpr (stable)
            {
                std::inclusive_scan(count.begin(), count.end(), count.begin());

                for (u32 i = n; i--;)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[--count[digit]] = arr[i] ^ post_sign_mask;
                }
            }
            else
            {
                std::exclusive_scan(
                    count.begin(),
                    count.end(),
                    count.begin(),
                    0);

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = arr[j];
                    temp[count[(v >> shift) & mask]++] = v ^ post_sign_mask;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            std::exclusive_scan(
                count.rbegin(),
                count.rend(),
                count.rbegin(),
                UT{0});

            for (u32 i = 0; i != n; ++i)
            {
                UT v = (arr[i] >> shift) & mask;
                temp[count[v]++] = arr[i] ^ post_sign_mask;
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    FORCE_INLINE static void do_passes(
        std::span<UT> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
        NO_SANITIZERS HOT_PATH
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    FORCE_INLINE static void sort(std::span<T> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        if (arr.size()) do_passes(reinterpret_range<UT>(arr), pass_idx_seq);
    }
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np, capacity>::sort(arr);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    u32 capacity = 100'001,
    std::integral T>
FORCE_INLINE void stable_radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np, capacity>::sort(arr);
}

class Solution
{
public:
    inline static std::pair<u32, u32> rstr[100'000]{};

    u32 maxBuilding(
        const u32 n,
        std::vector<std::vector<int>>& restrictions) noexcept
    {
        u32 nr = 0;
        for (auto t :
             reinterpret_cast<std::vector<std::vector<u32>>&>(restrictions))
        {
            rstr[nr++] = {t[0], t[1]};
        }

        radix_sort<10, 2>(std::span{reinterpret_cast<u64*>(rstr), nr});

        u32 i = 1, i_max = 0;
        for (auto& [k, k_max] : rstr | std::views::take(nr))
        {
            u32 l = k - i;
            k_max = std::min(k_max, i_max + l);
            i = k, i_max = k_max;
        }
        u32 j = n, j_max = i_max + n - i, r = 0;
        for (auto& prev : rstr | std::views::take(nr) | std::views::reverse)
        {
            std::tie(i, i_max) = prev;
            i_max = std::min(i_max, j_max + j - i);
            u32 lo = std::min(i_max, j_max), hi = std::max(i_max, j_max);
            r = std::max(r, hi + (j - i - hi + lo) / 2);
            j = i, j_max = i_max;
        }
        r = std::max(r, j_max + (j - j_max - 1) / 2);
        return r;
    }
};
