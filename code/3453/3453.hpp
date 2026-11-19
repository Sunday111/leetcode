#include <algorithm>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "radix_sorter.hpp"
#include "reinterpret_range.hpp"

class Solution
{
public:
    struct Square
    {
        u32 l;
        u32 y;
    };

    double separateSquares(const std::vector<std::vector<int>>& squares)
    {
        const u32 n = cast<u32>(squares.size());
        static Square s[50000];

        u64 total_area = 0;
        u64 begin_y = 0;
        u64 end_y = 0;
        for (u32 i = 0; i != n; ++i)
        {
            const auto& square = squares[i];
            auto y = cast<u32>(square[1]);
            auto l = cast<u32>(square[2]);
            s[i] = Square{.l = ~l, .y = y};
            total_area += u64{l} * u64{l};
            begin_y = std::min<u64>(begin_y, y);
            end_y = std::max(end_y, u64{y} + u64{l});
        }

        radix_sort<8, 8>(reinterpret_range<u64>(std::span{s}.first(n)));

        const double target_area = cast<double>(total_area) / 2;
        double left = cast<double>(begin_y), right = cast<double>(end_y);

        while ((right - left) > 0.00001)
        {
            double y = 0.5 * (right - left) + left, area = 0;

            for (u32 i = 0; i != n && (area < target_area); ++i)
            {
                auto& square = s[i];
                if (square.y > y) break;
                u32 l = ~square.l;
                area += std::min<double>(l, y - square.y) * l;
            }

            if (area < target_area)
            {
                left = y;
            }
            else
            {
                right = y;
            }
        }

        return left;
    }
};
