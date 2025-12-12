#include "aoc_2025_12.hpp"

namespace part1
{

struct Solver
{
    std::span<const Figure, 6> figures;
    std::span<const u8, 6> num_figures;
    u32 w{};
    u32 h{};

    std::array<std::bitset<64>, 64> board{};

    bool can_fit() const
    {
        std::array<u32, 6> fig_popcounts{};
        stdr::copy(
            figures | stdv::transform(&Figure::popcount),
            fig_popcounts.begin());

        {
            u32 req_popcnt = 0;
            for (auto [num_required, figure, fig_popcount] :
                 stdv::zip(num_figures, figures, fig_popcounts))
            {
                req_popcnt += num_required * fig_popcount;
            }
            if (req_popcnt > (w * h)) return false;
        }

        const u32 tot_num_figures =
            stdr::fold_left(num_figures, u32{}, std::plus{});

        {
            if (tot_num_figures <= (w / 3) * (h / 3))
            {
                return true;
            }
        }

        logln("Dunno");
        return false;
    }
};

class Solution
{
public:
    u32 solve(
        std::span<const Figure, 6> figures,
        std::span<const Request> requests) noexcept
    {
        u32 r = 0;

        std::array<u32, 6> fig_popcounts{};
        stdr::copy(
            figures | stdv::transform(&Figure::popcount),
            fig_popcounts.begin());

        for (auto& request : requests)
        {
            const u32 w = request[0], h = request[1];

            const std::span<const u8, 6> fig_count =
                std::span{request}.last<6>();

            {
            }

            {
                u32 req_popcnt = 0;
                for (auto [num_required, figure, fig_popcount] :
                     stdv::zip(fig_count, figures, fig_popcounts))
                {
                    req_popcnt += num_required * fig_popcount;
                }
                if (req_popcnt > (w * h))
                {
                    continue;
                }
            }

            r +=
                Solver{
                    .figures = figures,
                    .num_figures = fig_count,
                    .w = w,
                    .h = h}
                    .can_fit();
        }

        logln("{}/{}", r, requests.size());

        return r;
    }
};
}  // namespace part1
