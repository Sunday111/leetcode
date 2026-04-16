#include <memory_resource>
#include <unordered_map>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "upd_min.hpp"

class Solution
{
public:
    inline static std::pmr::unsynchronized_pool_resource pool;

    [[nodiscard, gnu::always_inline]] static constexpr u32 reverse(
        u32 x) noexcept
    {
        u32 r = 0;
        while (x)
        {
            r = r * 10 + x % 10;
            x /= 10;
        }
        return r;
    }
    [[nodiscard]] static u32 impl(std::vector<u32>& nums) noexcept
    {
        std::pmr::unordered_map<u32, u32> m(&pool);
        u32 n = cast<u32>(nums.size()), r = ~u32{};
        m.reserve(2 * n);
        for (u32 i = 0; i != n; ++i)
        {
            u32 v = nums[i];
            if (auto it = m.find(v); it != m.end())
            {
                upd_min(r, i - it->second);
            }
            m[reverse(v)] = i;
        }
        return r;
    }

    int minMirrorPairDistance(std::vector<int>& nums) const noexcept
    {
        return std::bit_cast<int>(
            impl(reinterpret_cast<std::vector<u32>&>(nums)));
    }
};
