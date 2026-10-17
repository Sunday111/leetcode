#include <algorithm>
#include <vector>

#include "integral_aliases.hpp"
#include "mod/binomial_coefficient_mod.hpp"
#include "mod/factorial_mod.hpp"
#include "mod/mod_int_inv_precompute.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_next.hpp"
#include "pyramid_bitset/pbs_prev.hpp"
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
    inline static u16 node_id_map[1002];
    inline static Node nodes[1001];
    inline static u16 sizes[kNullNode + 1];
    inline static ModInt ways[kNullNode + 1];
    inline static constexpr auto factorials = factorials_mods<1000>();
    inline static constexpr auto inverse_factorials =
        mod_int_inv_precompute(factorials);

    // Two bitset layers for values 1..1000: O(n) construction.
    [[gnu::no_sanitize_address, gnu::flatten]]
    static void construct_tree(const std::vector<int>& nums) noexcept
    {
        nodes[0] = {};
        nodes[0].v = nums[0] & 1023;
        PyramidBitset<1001> inserted{};
        // A missing neighbour selects the root (the earliest inserted node).
        node_id_map[inserted.kCapacity] = 0;
        node_id_map[nodes[0].v] = 0;
        pbs_add(inserted, nums[0] & 1023);

        for (size_t i = 1; i != nums.size(); ++i)
        {
            u16 node_id = i & 0xFFFF;
            u16 value = nums[i] & 1023;
            auto next = pbs_next(inserted, value);
            auto prev = pbs_prev(inserted, value);
            const u16 parent_id =
                std::max(node_id_map[next], node_id_map[prev]);

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
            node_id_map[value] = node_id;
            pbs_add(inserted, value);
        }
    }

    [[gnu::no_sanitize_address, gnu::flatten]]
    u32 numOfWays(const std::vector<int>& nums) noexcept
    {
        construct_tree(nums);

        sizes[kNullNode] = 0;
        ways[kNullNode] = {1};
        for (size_t i = nums.size(); i != 0;)
        {
            const auto& node = nodes[--i];
            const u16 left = sizes[node.l];
            const u16 right = sizes[node.r];
            auto count = ways[node.l] * ways[node.r];
            if (left && right)
            {
                count *= binomial_coefficient(
                    factorials,
                    inverse_factorials,
                    left + right,
                    right);
            }
            sizes[i] = left + right + 1;
            ways[i] = count;
        }
        return ways[0].value - 1;
    }
};
