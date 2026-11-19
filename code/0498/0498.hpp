#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> findDiagonalOrder(
        std::vector<std::vector<int>>& m)
    {
        const size_t h = m.size();
        const size_t w = m.front().size();
        const size_t num_diagonals = (w + h) - 1;

        std::vector<int> r;
        r.reserve(w * h);

        const size_t max_y = h - 1;
        const size_t max_x = w - 1;

        size_t xs{}, xf{}, ys{}, yf{}, xi{}, yi{};
        for (size_t t = 0; t != num_diagonals; ++t)
        {
            if (t < h)
            {
                xs = 0;
                ys = t;
            }
            else
            {
                xs = (t - h) + 1;
                ys = max_y;
            }

            if (t < w)
            {
                xf = t;
                yf = 0;
            }
            else
            {
                xf = max_x;
                yf = (t - w) + 1;
            }

            if ((t % 2) == 0)
            {
                xi = xs;
                yi = ys;
                while (true)
                {
                    r.push_back(m[yi][xi]);
                    if (xi == xf && yi == yf) break;
                    ++xi;
                    --yi;
                }
            }
            else
            {
                xi = xf;
                yi = yf;
                while (true)
                {
                    r.push_back(m[yi][xi]);
                    if (xi == xs && yi == ys) break;
                    --xi;
                    ++yi;
                }
            }
        }

        return r;
    }
};
