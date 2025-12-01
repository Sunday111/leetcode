#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <ranges>
#include <span>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// Find an iterator to the first
template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectFirstFalse(
    Range&& range,
    Proj&& proj) noexcept
{
    return std::ranges::lower_bound(
        std::forward<Range>(range),
        false,
        std::greater{},
        std::forward<Proj>(proj));
}

template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectLastTrue(
    Range&& range,
    Proj&& proj) noexcept
{
    return bisectFirstFalse(
               std::forward<Range>(range),
               std::forward<Proj>(proj)) -
           1;
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

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

    inline static std::array<UT, base> count;
    inline static std::array<UT, 100'001> temp;

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
    std::integral T>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np>::sort(arr);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    std::integral T>
FORCE_INLINE void stable_radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np>::sort(arr);
}

inline static constexpr auto sum =
    []<typename Range>(
        Range&& range,
        auto init = std::ranges::range_value_t<Range>{}) INLINE_LAMBDA
{
    for (auto&& v : std::forward<Range>(range))
    {
        init += v;
    }

    return init;
};

class Solution
{
public:
    u64 maxRunTime(u32 n, std::vector<int>& batteries_)
    {
        auto batteries = reinterpret_range<u32>(batteries_);
        radix_sort<8, 4, SortOrder::Descending>(batteries);

        const std::span<const u32> active = batteries.first(n);
        const std::span<const u32> swaps = batteries.last(batteries.size() - n);
        if (swaps.empty()) return active.back();

        const u64 total = sum(batteries, u64{0});
        if (n == 1) return total;

        auto test = [&](u64 target) -> bool
        {
            if (active.back() >= target) return true;

            u32 rem = 0, next = 0;

            for (u32 charge : active | std::views::reverse)
            {
                if (charge >= target) break;

                u64 need = target - charge;
                while (need > rem && next != swaps.size())
                {
                    need -= rem;
                    rem = swaps[next++];
                }

                if (need > rem) return false;
                rem -= need;
            }

            return true;
        };

        return *bisectLastTrue(
            std::views::iota(u64{batteries.back()}, (total / u64{n}) + 1),
            test);
    }
};
