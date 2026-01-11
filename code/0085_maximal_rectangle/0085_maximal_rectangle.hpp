#include <vector>

/*
rows == matrix.length
cols == matrix[i].length
1 <= rows, cols <= 200
*/
class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    [[nodiscard]] static constexpr auto maximalRectangle(
        const std::vector<std::vector<char>>& m) noexcept
    {
        u8 h[200], px[200], ph[200], w = m.front().size() & 0xFF, i = 0xFF;
        std::fill_n(h, w, 0);
        u16 max_area = 0;

        for (auto& row : m)
        {
            for (u8 x = 0; x != w; ++x)
            {
                bool v = row[x] == '1';
                u8& hx = h[x];
                hx = (hx + 1) & -v;

                u8 pop_x = x;
                while (i != 0xFF && ph[i] >= hx)
                {
                    u16 area = ph[i] * (x - px[i]);
                    max_area = std::max(max_area, area);
                    pop_x = px[i--];
                }

                ++i;
                px[i] = pop_x;
                ph[i] = hx;
            }

            for (; i != 0xFF; --i)
            {
                u16 area = ph[i] * (w - px[i]);
                max_area = std::max(max_area, area);
            }
        }

        return max_area;
    }
};
