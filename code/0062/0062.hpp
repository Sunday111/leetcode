#include <array>
#include <cstdint>

using u32 = uint32_t;

class Solution
{
public:
    inline static constexpr auto kAns = []
    {
        constexpr u32 w = 100, h = 100;
        std::array<std::array<u32, w>, h> r;  // NOLINT
        r[0].fill(1);

        for (u32 y = 1; y != h; ++y)
        {
            auto& prev = r[y - 1];
            auto& curr = r[y];
            curr[0] = 1;
            for (u32 x = 1; x != w; ++x) curr[x] = curr[x - 1] + prev[x];
        }

        return r;
    }();

    [[nodiscard]] static u32 uniquePaths(u32 h, u32 w) noexcept
    {
        return kAns[h - 1][w - 1];
    }
};
