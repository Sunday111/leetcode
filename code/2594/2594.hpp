#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <ranges>
#include <vector>

class Solution
{
public:
    using u64 = uint64_t;
    using u32 = uint32_t;

    [[nodiscard]] inline static constexpr u64 repairCars(
        const std::vector<int>& ranks,
        const u32 cars) noexcept
    {
        std::array<std::pair<u32, u32>, 101> groups{};
        for (int rank : ranks) ++groups[rank & 0xFF].first;

        u32 g = 0, min_rank = 101;
        for (u32 i = 0; i != 101; ++i)
        {
            if (groups[i].first)
            {
                groups[g++] = {
                    groups[i].first,
                    i,
                };
                min_rank = std::min(min_rank, i);
            }
        }

        return *std::ranges::lower_bound(
            std::views::iota(u64{1}, u64{cars} * u64{cars} * u64{min_rank}),
            true,
            std::less{},
            [&](u64 t)
            {
                u32 can_fix = 0;
                for (u32 i = 0; i != g && can_fix < cars; ++i)
                {
                    auto [num_mechanics, rank] = groups[i];
                    can_fix +=
                        static_cast<u32>(std::sqrt(t / rank)) * num_mechanics;
                }

                return can_fix >= cars;
            });
    }
};
