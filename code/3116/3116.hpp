#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    static auto count_lcm(const std::vector<int>& a, long hi)
    {
        // index is bitset, value is lcm(a[bit], ...)
        std::array<long, 1u << 15> cache{};
        std::unordered_map<long, int> lf{};

        cache[0] = 1;
        for (auto bits : std::views::iota(1u, 1u << a.size()))
        {
            unsigned i = std::countr_zero(bits) & 31;
            auto l = std::lcm(cache[bits & ~(1u << i)], a[i]);
            cache[bits] = l;
            if (l < hi)
            {
                auto o = std::popcount(bits) & 1;
                lf[l] += o - !o;
            }
        }

        std::vector<std::pair<long, int>> o;
        o.reserve(lf.size());

        for (auto& [lcm, count] : lf)
        {
            o.emplace_back(lcm, count);
        }

        std::ranges::sort(o);

        return o;
    }

    auto findKthSmallest(const std::vector<int>& coins, long k) noexcept
    {
        const long hi = *std::ranges::min_element(coins) * k + 1;
        auto how_many = [lf = count_lcm(coins, hi)](long v)
        {
            auto x = 0L;

            for (auto& [lcm, count] : lf)
            {
                if (lcm > v) break;
                x += (v / lcm) * count;
            }

            return x;
        };
        return *std::ranges::lower_bound(
            std::views::iota(1L, hi),
            k,
            std::less{},
            how_many);
    }
};
