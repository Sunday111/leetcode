#include <algorithm>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "bump_allocator.hpp"
#include "bump_hash_map.hpp"
#include "bump_set.hpp"
#include "cast.hpp"
#include "ceil_div.hpp"
#include "empty.hpp"
#include "factorizer.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"

inline static const Factorizer<1'000'001, 100'001> factorizer;

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    static constexpr u32 impl(const std::vector<u32>& nums) noexcept
    {
        auto _ = SolutionStorage::Instance().StartArena();
        const u32 n = cast<u32>(nums.size());

        // next[i] saves the index in the array nums
        // such that nums[i] == nums[next[i]] or '~u32{}' if
        // this is the last element in the list of duplicates
        static u32 next[100'000];
        std::fill_n(next, n, ~u32{});

        // a map from a value to the index i in nums
        // which denotes the first element in the linked
        // list of duplicates
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> head;
        head->reserve(2 * n);

        for (u32 i = 0; i != n; ++i)
        {
            auto it = head->try_emplace(nums[i], ~u32{}).first;
            next[i] = std::exchange(it->second, i);
        }

        // Key is value in nums
        // value is a set of values in nums
        ObjectWithoutDtor<BumpHashMap<
            u32,
            ObjectWithoutDtor<BumpSet<u32, SolutionStorage>>,
            SolutionStorage>>
            edges;
        for (u32 i = 0; i != n; ++i)
        {
            u32 v = nums[i];

            for (u32 x = v; x > 1;)
            {
                u32 prime = factorizer.spf[x];
                while (!(x % prime)) x /= prime;

                if (head->contains(prime))
                {
                    edges.get()[prime]->insert(v);
                }
            }
        }

        static u64 visited_words[ceil_div(100'000, 64)];
        std::fill_n(visited_words, ceil_div(n, 64), 0);
        PyramidBitset<100'000> a(kEmpty, n), b(kEmpty, n);

        auto front = &a, back = &b;

        auto visited = [] [[gnu::always_inline]] (u32 i)
        {
            auto& w = visited_words[i >> 6];
            return w & (u64{1} << (i & 63));
        };
        auto visit = [] [[gnu::always_inline]] (u32 i)
        {
            auto& w = visited_words[i >> 6];
            w |= (u64{1} << (i & 63));
        };

        u32 queue_size = 1;
        front->add(0);

        for (u32 step = 0;; ++step)
        {
            u32 next_size = 0;
            auto enqueue = [&] [[gnu::always_inline]] (u32 j) noexcept
            {
                next_size += back->add_ex(j & -u32{!visited(j)});
            };

            while (queue_size--)
            {
                u32 i = front->max();
                front->remove(i);

                if (i + 1 == n) return step;
                if (visited(i)) continue;
                visit(i);

                if (i && !visited(i - 1)) enqueue(i - 1);
                enqueue(i + 1);

                u32 v = nums[i];
                auto it = edges->find(v);
                if (it == edges->end()) continue;

                for (auto& vj : it->second.get())
                {
                    auto it2 = head->find(vj);
                    if (it2 == head->end()) continue;
                    for (u32 j = it2->second; j != ~u32{}; j = next[j])
                    {
                        enqueue(j);
                    }
                    head->erase(it2);
                }
            }

            queue_size = next_size;
            std::swap(front, back);
        }

        std::unreachable();
    }

    u32 minJumps(std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<std::vector<u32>&>(nums));
    }
};
