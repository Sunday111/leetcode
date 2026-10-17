#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

class Solution
{
public:
    [[nodiscard]] auto findSmallestSetOfVertices(
        const u32 n,
        const std::vector<std::vector<int>>& edges)
    {
        static PyramidBitset<100'001> is_root;
        pbs_initialize(is_root, kFull, n + 1);

        for (auto& e : edges)
        {
            pbs_remove(is_root, cast<u32>(e[1]));
        }

        std::vector<int> r;

        while (true)
        {
            auto i = pbs_min(is_root);
            if (i >= n) break;
            r.emplace_back(static_cast<int>(i));
            pbs_remove(is_root, i);
        }

        return r;
    }
};
