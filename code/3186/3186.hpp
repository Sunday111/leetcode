#include <algorithm>
#include <array>
#include <span>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;

    static u64 maximumTotalDamage(std::vector<int>& power_) noexcept
    {
        const std::span<u32> power = reinterpret_range<u32>(power_);

        if (power.size() < 10'000)
        {
            radix_sort<6, 5>(power);
        }
        else
        {
            radix_sort<15, 2>(power);
        }

        static std::array<u64, 100'001> arr;

        u32 n = 0xFFFFFFFF, h = 0;
        for (u32 v : power)
        {
            n += v != h;
            power[n] = v;
            arr[n] *= v == std::exchange(h, v);
            arr[n]++;
        }
        ++n;

        u64 r = 0;

        std::array<u32, 3> p{};
        p.fill(0xFFFFFFFF - 10);
        std::array<u64, 4> v{};
        for (u32 i = 0; i != n; ++i)
        {
            p[0] = power[i];
            const bool c1 = p[1] < p[0], c2 = p[2] < p[0];
            v[0] = arr[i] * p[0] + v[!c1 * (c2 * 2 + !c2 * 3) + c1];
            v[0] = r = std::max(r, v[0]);
            p[2] = p[1], p[1] = p[0] + 2;
            v[3] = v[2], v[2] = v[1], v[1] = v[0];
        }

        return r;
    }
};

#include "sync_stdio.hpp"
