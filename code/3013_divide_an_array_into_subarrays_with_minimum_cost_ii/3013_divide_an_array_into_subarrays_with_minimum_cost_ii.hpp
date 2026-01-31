#include <vector>

#include "bump_multiset.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"

using SolutionStorage = GlobalBufferStorage<1u << 25>;

struct SumKSmallest
{
    u32 k{};
    u64 sum = 0;
    BumpMultiset<u32, SolutionStorage> smallest{};
    BumpMultiset<u32, SolutionStorage> other{};

    FORCE_INLINE void insert(u32 v) noexcept
    {
        if (smallest.size() < k)
        {
            smallest.insert(v);
            sum += v;
        }
        else
        {
            auto it = std::prev(smallest.end());
            if (v < *it)
            {
                other.insert(*it);
                sum -= *it;

                auto node = smallest.extract(it);
                sum += v;
                node.value() = v;
                smallest.insert(std::move(node));
            }
            else
            {
                other.insert(v);
            }
        }
    }

    FORCE_INLINE void erase(u32 v) noexcept
    {
        if (auto it = other.find(v); it != other.end())
        {
            other.erase(it);
        }
        else
        {
            it = smallest.find(v);
            sum -= *it;
            smallest.erase(it);

            if (!other.empty())
            {
                auto it2 = other.begin();
                sum += *it2;
                smallest.insert(*it2);
                other.erase(it2);
            }
        }
    }

    [[nodiscard]] FORCE_INLINE constexpr u32 size() noexcept
    {
        return static_cast<u32>(smallest.size() + other.size());
    }
};

class Solution
{
public:
    [[nodiscard]] static auto
    minimumCost(std::vector<u32>& nums, u32 k, u32 dist) noexcept
    {
        auto& storage = SolutionStorage::Instance();
        auto arena = storage.StartArena();

        ObjectWithoutDtor<SumKSmallest> s;
        s->k = k - 2;

        u64 r = std::numeric_limits<long>::max();
        u32 n = static_cast<u32>(nums.size());

        for (u32 i = 1; i <= dist; ++i) s->insert(nums[i]);

        for (u32 i1 = 1, ik = 1 + dist; ik != n; ++i1, ++ik)
        {
            s->erase(nums[i1]);
            s->insert(nums[ik]);
            r = std::min(r, nums[i1] + s->sum);
        }

        for (u32 i = n - s->size(); !s->other.empty(); ++i)
        {
            s->erase(nums[i]);
            r = std::min(r, nums[i] + s->sum);
        }

        return r + nums[0];
    }

    [[nodiscard]] static auto
    minimumCost(std::vector<int>& nums, u32 k, u32 dist) noexcept
    {
        return minimumCost(reinterpret_cast<std::vector<u32>&>(nums), k, dist);
    }
};
