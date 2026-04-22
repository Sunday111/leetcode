#include <string>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    std::vector<std::string> twoEditWords(
        std::vector<std::string>& queries,
        std::vector<std::string>& d) noexcept
    {
        u32 t = 0;

        auto good_dist =
            [l = cast<u8>(queries[0].size())] [[gnu::always_inline]] (
                std::string & a,
                std::string & b) noexcept
        {
            u8 dist = 0;
            for (u8 i = 0; i != l && dist != 3; ++i) dist += a[i] != b[i];
            return dist != 3;
        };

        for (auto& q : queries)
        {
            for (auto& w : d)
            {
                if (good_dist(q, w))
                {
                    std::swap(queries[t++], q);
                    break;
                }
            }
        }

        queries.resize(t);
        return std::move(queries);
    }
};
