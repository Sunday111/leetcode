#pragma once

#include <algorithm>
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

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::unsigned_integral T,
    SortOrder order,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
struct RadixSorter
{
    [[nodiscard]] static std::vector<T>& get_static_data() noexcept
    {
        static std::vector<T> v;
        v.reserve(100'001);
        return v;
    }

    static constexpr T base = 1u << bits_per_pass;
    static constexpr T mask = base - 1;

    template <u8 pass>
    ATTR static void radixSortPass(
        std::span<T> arr,
        std::array<T, base>& count) noexcept
    {
        auto& temp = get_static_data();

        count.fill(0);
        constexpr T shift = pass * bits_per_pass;

        // Count digit occurrences
        for (auto v : arr) ++count[(v >> shift) & mask];

        const u32 n = static_cast<u32>(arr.size());

        if constexpr (order == SortOrder::Ascending)
        {
            // Prefix sums for positions
            for (u32 i = 1; i < base; ++i) count[i] += count[i - 1];

            // Stable placement
            u32 i = n;
            do
            {
                --i;
                u32 digit = (arr[i] >> shift) & mask;
                temp[--count[digit]] = arr[i];
            } while (i);
        }
        else
        {
            // Compute descending start positions directly
            T sum = 0;
            for (u32 i = base; i-- > 0;)
            {
                T c = count[i];
                count[i] = sum;
                sum += c;
            }

            // Stable placement
            for (u32 i = 0; i != n; ++i)
            {
                u32 digit = (arr[i] >> shift) & mask;
                temp[count[digit]++] = arr[i];
            }
        }

        std::ranges::copy(temp, arr.begin());
    }

    ATTR static void radixSort(std::span<T> arr) noexcept
    {
        u32 n = static_cast<u32>(arr.size());
        if (n == 0) return;

        auto& temp = get_static_data();
        temp.clear();
        temp.resize(n);

        std::array<T, base> count{};

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
    [[nodiscard]] ATTR static auto reinterpret_span(
        std::span<From, extent> in) noexcept
    {
        return std::span<To, extent>{
            reinterpret_cast<To*>(in.data()),  // NOLINT
            in.size()};
    }

    [[nodiscard]] static constexpr size_t matchPlayersAndTrainers(
        std::vector<int>& players,
        std::vector<int>& trainers) noexcept
    {
        RadixSorter<u32, SortOrder::Descending, 6, 5>::radixSort(
            reinterpret_span<u32>(std::span{players}));
        RadixSorter<u32, SortOrder::Descending, 6, 5>::radixSort(
            reinterpret_span<u32>(std::span{trainers}));

        size_t np = players.size(), nt = trainers.size();
        size_t ip = 0, it = 0, r = 0;
        while (ip != np && it != nt)
        {
            bool match = players[ip] <= trainers[it];
            it += match;
            r += match;
            ++ip;
        }

        return r;
    }
};
