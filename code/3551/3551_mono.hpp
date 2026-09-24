#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <functional>
#include <type_traits>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

struct RadixSortIndicesByStorage
{
    template <std::unsigned_integral I, u32 capacity>
    inline static I scratch[capacity];

    alignas(u32) inline static u8 counts[sizeof(u32) << 16];
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    u32 capacity = 100'001,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
radix_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    using Count = UintForValue<capacity>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(bits_per_pass > 0 && bits_per_pass <= 16);

    constexpr u32 radix = 1u << bits_per_pass;
    constexpr Key mask = radix - 1;
    constexpr u32 max_passes =
        (sizeof(Key) * 8 + bits_per_pass - 1) / bits_per_pass;
    constexpr u32 passes = num_passes == 0xFFFFFFFF ? max_passes : num_passes;
    static_assert(passes <= max_passes);

    auto* counts = reinterpret_cast<Count*>(RadixSortIndicesByStorage::counts);
    assert(n <= capacity);  // NOLINT
    I* src = indices;
    I* dst = RadixSortIndicesByStorage::scratch<I, capacity>;

    for (u32 pass = 0; pass < passes; ++pass)
    {
        std::memset(counts, 0, radix * sizeof(Count));
        const u32 shift = pass * bits_per_pass;
        for (u32 pos = 0; pos < n; ++pos)
        {
            ++counts[(proj(src[pos]) >> shift) & mask];
        }

        for (u32 i = 1; i < radix; ++i)
        {
            counts[i] += counts[i - 1];
        }
        for (u32 pos = n; pos--;)
        {
            const I index = src[pos];
            const Key digit = (proj(index) >> shift) & mask;
            dst[--counts[digit]] = index;
        }
        std::swap(src, dst);
    }
    if (passes % 2 && n)
    {
        std::memcpy(indices, src, n * sizeof(I));
    }
}

template <
    u32 key_bits,
    u32 capacity = 100'001,
    std::unsigned_integral I,
    typename Proj>
[[gnu::no_sanitize_address, gnu::flatten]] void
adaptive_sort_indices_by(I* indices, u32 n, Proj proj) noexcept
{
    using Key = std::remove_cvref_t<std::invoke_result_t<Proj&, I>>;
    static_assert(std::unsigned_integral<Key>);
    static_assert(key_bits > 0 && key_bits <= sizeof(Key) * 8);
    assert(n <= capacity);  // NOLINT

    if (n < 256)
    {
        std::ranges::sort(indices, indices + n, std::less{}, proj);
    }
    else if (n < 1280)
    {
        radix_sort_indices_by<
            std::min(8u, key_bits),
            (key_bits + 7) / 8,
            std::min(capacity, 1279u)>(indices, n, proj);
    }
    else if (n < 8192)
    {
        radix_sort_indices_by<
            std::min(10u, key_bits),
            (key_bits + 9) / 10,
            std::min(capacity, 8191u)>(indices, n, proj);
    }
    else
    {
        radix_sort_indices_by<
            std::min(13u, key_bits),
            (key_bits + 12) / 13,
            capacity>(indices, n, proj);
    }
}
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    inline static constexpr auto kDigitSums = []
    {
        std::array<u8, 100'000> table{};
        auto* data = table.data();
        for (u32 i = 1; i != table.size(); ++i)
        {
            data[i] = (data[i / 10] + i % 10) & 0xFF;
        }
        return table;
    }();

    [[nodiscard,
      gnu::target("bmi2,avx2"),
      gnu::always_inline,
      gnu::no_sanitize_address,
      gnu::flatten]] static u8
    digitSum(u32 x) noexcept
    {
        return static_cast<u8>(
            kDigitSums[x % 100'000] + kDigitSums[x / 100'000]);
    }

    inline static u8 sums[100'000];
    alignas(u32) inline static u8 sorted_storage[sizeof(u32) * 100'000];

    template <u32 kMaxN>
    [[gnu::target("bmi2,avx2"), gnu::no_sanitize_address, gnu::flatten]]
    static u32 impl(const std::vector<int>& nums) noexcept
    {
        using Index = UintForValue<kMaxN>;
        static_assert(sizeof(Index) * kMaxN <= sizeof(sorted_storage));
        auto* sorted = reinterpret_cast<Index*>(sorted_storage);
        const auto* a = reinterpret_cast<const u32*>(nums.data());
        const u32 n = static_cast<u32>(nums.size());

        for (u32 i = 0; i != n; ++i)
        {
            sums[i] = digitSum(a[i]);
            sorted[i] = static_cast<Index>(i);
        }

        auto proj = [a] [[gnu::always_inline, gnu::no_sanitize_address]] (
                        Index i) -> u64
        {
            return (u64{sums[i]} << 30) | a[i];
        };

        adaptive_sort_indices_by<37, kMaxN>(sorted, n, proj);

        u32 num_swaps = 0;

        for (u32 i = 0; i != n; ++i)
        {
            while (sorted[i] != i)
            {
                std::swap(sorted[i], sorted[sorted[i]]);
                ++num_swaps;
            }
        }

        return num_swaps;
    }

    [[gnu::target("bmi2,avx2"), gnu::no_sanitize_address, gnu::flatten]]
    u32 minSwaps(const std::vector<int>& nums) const noexcept
    {
        if (nums.size() <= 65'535) return impl<65'535>(nums);
        return impl<100'000>(nums);
    }
};
