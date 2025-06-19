#pragma once

#include <algorithm>
#include <span>
#include <vector>

using u8 = uint8_t;
using u32 = uint32_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

template <u8 bits_per_pass>
struct RadixSorter
{
    [[nodiscard]] static std::vector<u32>& get_static_data() noexcept
    {
        static std::vector<u32> v;
        v.reserve(100'000);
        return v;
    }

    static constexpr u8 num_passes = (31 + bits_per_pass) / bits_per_pass;
    static constexpr u32 base = 1u << bits_per_pass;
    static constexpr u32 mask = base - 1;

    template <u8 pass>
    ATTR static void radixSortPass(
        std::span<u32> arr,
        std::array<u32, base>& count) noexcept
    {
        auto& temp = get_static_data();

        count.fill(0);
        constexpr u32 shift = pass * bits_per_pass;

        // Count digit occurrences
        for (auto v : arr) ++count[(v >> shift) & mask];

        // Prefix sums for positions
        for (u32 i = 1; i < base; ++i) count[i] += count[i - 1];

        // Stable placement
        u32 i = static_cast<u32>(arr.size());
        do
        {
            --i;
            u32 digit = (arr[i] >> shift) & mask;
            temp[--count[digit]] = arr[i];
        } while (i);

        std::ranges::copy(temp, arr.begin());
    }

    ATTR static void radixSort(std::span<u32> arr) noexcept
    {
        u32 n = static_cast<u32>(arr.size());
        if (n == 0) return;

        auto& temp = get_static_data();
        temp.clear();
        temp.resize(n);

        std::array<u32, base> count{};

        [&]<u8... pass>(std::integer_sequence<u8, pass...>)
        {
            (radixSortPass<pass>(arr, count), ...);
        }(std::make_integer_sequence<u8, num_passes>());
    }
};

class Solution
{
public:
    template <typename To, typename From, size_t extent = std::dynamic_extent>
    [[nodiscard]] static auto reinterpret_span(
        std::span<From, extent> in) noexcept
    {
        return std::span<To, extent>{
            reinterpret_cast<To*>(in.data()),  // NOLINT
            in.size()};
    }

    [[nodiscard]] static int partitionArray(
        std::vector<int>& nums,
        int k) noexcept
    {
        RadixSorter<6>::radixSort(reinterpret_span<u32>(std::span{nums}));

        int r = 0, t = -1;
        for (int v : nums)
        {
            if (v > t)
            {
                ++r;
                t = v + k;
            }
        }

        return r;
    }
};
