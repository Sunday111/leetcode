#include <array>
#include <bit>
#include <string>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    i64 minimumCost(
        std::string& source,
        std::string& target,
        std::vector<char>& original,
        std::vector<char>& changed,
        std::vector<int>& change_cost) noexcept
    {
        std::array<u32, 26> bitsets{};
        std::array<std::array<u32, 26>, 26> cost;  // NOLINT
        for (auto& x : cost) x.fill(1000000000);

        for (u32 i = 0; i != original.size(); ++i)
        {
            u8 from = cast<u8>(original[i] - 'a'),
               to = cast<u8>(changed[i] - 'a');
            cost[from][to] =
                std::min(cost[from][to], cast<u32>(change_cost[i]));
            bitsets[from] |= (1u << to);
        }

        for (u8 k = 0; k != 26; ++k)
        {
            for (u8 i = 0; i != 26; ++i)
            {
                u32& bi = bitsets[i];
                if (!(bi & (1u << k))) continue;

                for (u32 bk = bitsets[k]; bk;)
                {
                    u8 j = cast<u8>(std::countr_zero(bk));
                    bk &= ~(1u << j);
                    cost[i][j] = std::min(cost[i][j], cost[i][k] + cost[k][j]);
                    bi |= (1u << j);
                }
            }
        }

        for (u8 i = 0; i != 26; ++i)
        {
            cost[i][i] = 0;
            bitsets[i] |= (1u << i);
        }

        u64 r = 0, k = source.size();
        for (u32 i = 0; i != k; ++i)
        {
            u8 from = cast<u8>(source[i] - 'a'), to = cast<u8>(target[i] - 'a');
            if (!(bitsets[from] & (1u << to))) return -1;
            r += cost[from][to];
        }

        return cast<i64>(r);
    }
};
