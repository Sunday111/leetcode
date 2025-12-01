#include <integral_aliases.hpp>
#include <unordered_map>
#include <vector>

#include "bump_hash_map.hpp"
#include "bump_vector.hpp"
#include "cast.hpp"
#include "reinterpret_range.hpp"

class Solution
{
private:
    using SolutionStorage = GlobalBufferStorage<1 << 25>;
    static constexpr size_t kArrayCapacity = 100'000;

    [[nodiscard]] static int
    solve_map(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> m;
        m->reserve(2 * n);
        m.get()[0] = ~0u;
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            if (auto it = m->find(x); it != m->end())
            {
                r = std::min(i - it->second, r);
            }
            m.get()[s] = i;
        }
        return r == n ? -1 : cast<int>(r);
    }

    [[nodiscard]] static int
    solve_arr(std::span<const u32> nums, u32 p, u32 n, u32 target) noexcept
    {
        u32 r = n;
        BumpVector<u32, SolutionStorage> m;
        m.resize(p, 2 * n);

        m[0] = ~0u;
        for (u32 i = 0; i != n; ++i)
        {
            u32 s = nums[i], x = (s + p - target) % p;
            r = std::min(i - m[x], r);
            m[s] = i;
        }
        return r == n ? -1 : cast<int>(r);
    }

public:
    [[nodiscard]] static int minSubarray(
        std::vector<int>& nums_,
        u32 p) noexcept
    {
        auto arena = SolutionStorage::Instance().StartArena();
        const auto nums = reinterpret_range<u32>(nums_);
        u32 target = 0, n = cast<u32>(nums.size());
        for (u32& v : nums) v = ((target += v) %= p);
        if (target == 0) return 0;  // No action needed
        auto fn = (p > kArrayCapacity || p > n) ? solve_map : solve_arr;
        return fn(nums, p, n, target);
    }
};
