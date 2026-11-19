#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"

class Solution
{
public:
    u32 countCoveredBuildings(int n, std ::vector<std::vector<int>>& buildings)
    {
        static std::pair<u32, u32> mx[100'001], my[100'001];
        constexpr std::pair lim{100'001, 0};
        fill_n(mx, n + 1, lim);
        fill_n(my, n + 1, lim);

        for (auto& p : buildings)
        {
            u32 x = cast<u32>(p[0]), y = cast<u32>(p[1]);
            auto& [lox, hix] = my[y];
            auto& [loy, hiy] = mx[x];
            loy = std::min(loy, y);
            hiy = std::max(hiy, y);
            lox = std::min(lox, x);
            hix = std::max(hix, x);
        }
        u32 r = 0;
        for (auto& p : buildings)
        {
            u32 x = cast<u32>(p[0]), y = cast<u32>(p[1]);
            auto& [loy, hiy] = mx[x];
            auto& [lox, hix] = my[y];
            r += x != lox && x != hix && y != loy && y != hiy;
        }

        return r;
    }
};
