#include <algorithm>
#include <array>
#include <vector>

#include "adaptive_sort_indices_by.hpp"
#include "integral_aliases.hpp"
#include "sync_stdio.hpp"
#include "uint_for_value.hpp"

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
