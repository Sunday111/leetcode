#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_min.hpp"
#include "pyramid_bitset/pbs_remove.hpp"

class Solution
{
public:
    [[nodiscard]] auto findSmallestSetOfVertices(
        const u32 n,
        const std::vector<std::vector<int>>& edges)
    {
        static u64 is_root_words[PyramidBitset<100'001>::kTotalWords]{};
        static auto is_root = pbs_make<100'001>(is_root_words);
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
