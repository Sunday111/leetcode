#include <vector>

class Solution
{
public:
    using u64 = uint64_t;
    int countCompleteComponents(int n, std::vector<std::vector<int>>& edges)
    {
        constexpr u64 z{0}, o{1};
        u64 adj[64]{}, v = ~z << n;
        int r = 0;

        // Diagonal (an edge from node to self)
        while (n--) adj[n] = o << n;

        // Fill adjacency graph
        for (auto& e : edges)
        {
            int i = e[0], j = e[1];
            adj[i] |= o << j;
            adj[j] |= o << i;
        }

        // While there is something not visited
        while (v != ~z)
        {
            u64 m = adj[std::countr_one(v)];
            bool ok = true;
            // Check that each neighbor has the same links
            // (completness criteria for component)
            for (u64 q = m; q && ok;)
            {
                int j = std::countr_zero(q);
                q &= ~(o << j);
                ok = adj[j] == m;
            }
            r += ok;

            // Mark the whole component as visited
            v |= m;
        }

        return r;
    }
};
