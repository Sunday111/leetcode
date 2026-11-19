#include <format>
#include <string>
#include <vector>

#include "ncr.hpp"
#include "next_with_same_popcount.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::string> readBinaryWatch(
        u8 k) noexcept
    {
        if (k == 0) return {"0:00"};
        if (k > 8) return {};

        std::vector<std::string> res;
        res.reserve(ncr(9, k));

        for (u16 q = ((u16{1} << k) - 1) & 0xFFFF; q < (1 << 10);
             q = next_with_same_popcount(q))
        {
            u8 hour = (q >> 6) & 0xFF, min = q & 63;
            if (hour < 12 && min < 60)
            {
                res.emplace_back(std::format("{}:{:02}", hour, min));
            }
        }

        return res;
    }
};
