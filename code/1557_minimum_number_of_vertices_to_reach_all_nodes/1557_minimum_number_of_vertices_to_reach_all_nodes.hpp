#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset.hpp"

class Solution
{
public:
    [[nodiscard]] auto findSmallestSetOfVertices(
        const u32 n,
        const std::vector<std::vector<int>>& edges)
    {
        static PyramidBitset<100'001> is_root;
        is_root.initialize(kFull, n + 1);

        for (auto& e : edges)
        {
            is_root.remove(cast<u32>(e[1]));
        }

        std::vector<int> r;

        while (true)
        {
            auto i = is_root.min();
            if (i >= n) break;
            r.emplace_back(static_cast<int>(i));
            is_root.remove(i);
        }

        return r;
    }
};
