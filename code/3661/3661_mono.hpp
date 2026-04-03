#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <span>
#include <utility>
#include <vector>






template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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

using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] static constexpr u64 pack(
        int b,
        int a) noexcept
    {
        return (u64{std::bit_cast<u32>(a)} << 32) | u64{std::bit_cast<u32>(b)};
    }

    [[nodiscard, gnu::always_inline]] static constexpr std::tuple<int, int>
    unpack(u64 p) noexcept
    {
        u32 b = (p >> 32) & ~u32{};
        u32 a = (p >> 0) & ~u32{};
        return {std::bit_cast<int>(a), std::bit_cast<int>(b)};
    }

    u32 maxWalls(
        std::vector<int>& positions,
        std::vector<int>& distances,
        std::vector<int>& walls) noexcept
    {
        u32 nr = static_cast<u32>(positions.size());
        u32 nw = static_cast<u32>(walls.size());

        static u64 robots[100'002];

        robots[0] = pack(0, 0);
        for (u32 i = 0; i != nr; ++i)
        {
            robots[i + 1] = pack(positions[i], distances[i]);
        }
        robots[nr + 1] = pack(INT_MAX, 0);

        radix_sort<10, 3>(std::span{robots + 1, nr});
        radix_sort<10, 3>(reinterpret_range<u32>(std::span{walls}));

        int* we = walls.data() + nw;
        int *a = walls.data(), *c = a;
        int* b = walls.data();

        u32 na = 0, nb = 0;

        auto dist =
            [] [[nodiscard, gnu::always_inline]] (auto a, auto b) noexcept
        {
            return static_cast<u32>(std::distance(a, b));
        };

        for (u32 ri = 1; ri != nr + 1; ++ri)
        {
            auto [p, d] = unpack(robots[ri]);
            int l = p - d;
            int r = p + d;

            {
                auto [prev, _1] = unpack(robots[ri - 1]);
                l = std::max(l, prev + 1);
                auto [next, _2] = unpack(robots[ri + 1]);
                r = std::min(r, next - 1);
            }

            // add reachable
            while (c != we && *c <= r) ++c;

            // remove unreachable
            while (a != c && *a < l) ++a;
            b = std::max(a, b);

            auto at_robot = a;
            while (at_robot != c && *at_robot < p) ++at_robot;

            auto after_robot = at_robot + (at_robot != c && *at_robot == p);
            u32 lla = na + dist(a, after_robot);
            u32 lra = na + dist(at_robot, c);
            u32 llb = nb + dist(b, after_robot);
            u32 lrb = nb + dist(at_robot, c);

            a = after_robot;
            b = c;

            na = std::max(lla, llb);
            nb = std::max(lra, lrb);
        }
        return std::max(na, nb);
    }
};
