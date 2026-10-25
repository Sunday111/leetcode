#include <vector>

#include "integral_aliases.hpp"
#include "mod/binomial_coefficient_mod.hpp"
#include "mod/factorial_mod.hpp"
#include "mod/mod_int_inv_precompute.hpp"
#include "sync_stdio.hpp"

struct Node
{
    u16 v{};
    u16 l = 0xFFFF;
    u16 r = 0xFFFF;
};

class Solution
{
public:
    inline static Node nodes[1001];
    inline static u16 q[1001];
    inline static constexpr auto factorials = factorials_mods<1000>();
    inline static constexpr auto inverse_factorials =
        mod_int_inv_precompute(factorials);

    u32 numOfWays(const std::vector<int>& nums) noexcept
    {
        u16 next_node = 0;

        Node* root = &nodes[next_node++];
        *root = {};
        root->v = nums[0] & 0xFFFF;

        auto insert = [&](this auto&& f, Node* x, u16 v) -> void
        {
            u16& t = v < x->v ? x->l : x->r;
            if (t != 0xFFFF)
            {
                f(&nodes[t], v);
            }
            else
            {
                t = next_node++;
                (nodes[t] = {}).v = v;
            }
        };

        for (size_t i = 1; i != nums.size(); ++i)
        {
            insert(root, nums[i] & 0xFFFF);
        }

        auto [_, x] = [&](this auto&& dfs,
                          u16 node_id) -> std::pair<u16, ModInt>
        {
            if (node_id == 0xFFFF) return {0, {1}};

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
