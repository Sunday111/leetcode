#include <algorithm>
#include <array>
#include <vector>

#include "integral_aliases.hpp"
#include "mod/binomial_coefficient_mod.hpp"
#include "mod/factorial_mod.hpp"
#include "mod/mod_int_inv_precompute.hpp"
#include "pyramid_bitset.hpp"
#include "sync_stdio.hpp"

inline constexpr u32 kNullNode = 1023;

struct Node
{
    u32 v : 10 = 0;
    u32 l : 10 = kNullNode;
    u32 r : 10 = kNullNode;
};

class Solution
{
public:
    inline static Node nodes[1001];
    inline static u16 q[1001];
    inline static constexpr auto factorials = factorials_mods<1000>();
    inline static constexpr auto inverse_factorials =
        mod_int_inv_precompute(factorials);

    static void construct_tree(const std::vector<int>& nums) noexcept
    {
        nodes[0] = {};
        nodes[0].v = nums[0] & 1023;
        std::array<u16, 1001> node_ids;  // NOLINT
        PyramidBitset<1001> inserted{kEmpty};
        node_ids[nodes[0].v] = 0;
        inserted.add(nums[0] & 1023);

        for (size_t i = 1; i != nums.size(); ++i)
        {
            u16 node_id = i & 0xFFFF;
            u16 value = nums[i] & 1023;
            auto next = inserted.successor(value);
            auto prev = inserted.predecessor(value);
            u16 parent_id = 0;
            if (next != inserted.get_capacity()) parent_id = node_ids[next];
            if (prev != inserted.get_capacity())
            {
                parent_id = std::max(parent_id, node_ids[prev]);
            }

            nodes[node_id] = {};
            nodes[node_id].v = nums[i] & 1023;
            auto& parent = nodes[parent_id];
            if (nums[i] < parent.v)
            {
                parent.l = node_id;
            }
            else
            {
                parent.r = node_id;
            }
            node_ids[value] = node_id;
            inserted.add(value);
        }
    }

    u32 numOfWays(const std::vector<int>& nums) noexcept
    {
        construct_tree(nums);

        auto [_, x] = [&](this auto&& dfs,
                          u16 node_id) -> std::pair<u16, ModInt>
        {
            if (node_id == kNullNode) return {0, {1}};

            auto [num, ways] = dfs(nodes[node_id].l);
            auto [rnum, rways] = dfs(nodes[node_id].r);
            num += rnum;
            ways *= rways;

            if ((!!num) & (num != rnum))
            {
                ways *= binomial_coefficient(
                    factorials,
                    inverse_factorials,
                    num,
                    rnum);
            }

            return {num + 1, ways};
        }(0);

        return x.value - 1;
    }
};
