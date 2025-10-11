#include <algorithm>
#include <array>
#include <span>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr size_t subarrayBitwiseORs(
        std::vector<i32>& arr) noexcept
    {
        auto a = reinterpret_range<u32>(arr);

        static std::array<u32, 1'000'001> results;
        u32 num_results = 0;

        const u32 n = static_cast<u32>(a.size());
        for (u32 i = 0; i != n; ++i)
        {
            const u32 x = a[i];
            u32 skip = 0, take = x;
            results[num_results++] = take;
            for (u32 j = i; j--;)
            {
                skip |= a[j];
                take = skip | x;
                if (skip == take) break;
                results[num_results++] = take;
            }
        }

        auto numbers = std::span{results}.first(num_results);
        radix_sort<u32, SortOrder::Ascending, 8>(numbers);
        return numbers.size() - std::ranges::unique(numbers).size();
    }
};
