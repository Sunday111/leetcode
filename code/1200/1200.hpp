#include <vector>

#include "radix_sort/radix_sort.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr auto minimumAbsDifference(
        std::vector<int>& arr) noexcept
    {
        radix_sort<32, 8>(arr.data(), static_cast<u32>(arr.size()));
        const auto n = arr.size();

        std::vector<std::vector<int>> r;
        r.reserve(n);
        int md = arr.back() - arr.front();
        for (size_t i = 0, j = 1; j != n; ++i, ++j)
        {
            int a = arr[i], b = arr[j], d = b - a;

            if (d < md)
            {
                r.clear();
                md = d;
            }

            if (d == md)
            {
                r.emplace_back() = {a, b};
            }
        }

        return r;
    }
};
