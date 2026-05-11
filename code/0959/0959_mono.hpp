#include <cstdint>
#include <numeric>
#include <string>
#include <utility>
#include <vector>




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    u32 regionsBySlashes(std::vector<std::string>& g)
    {
        const u32 n = cast<u32>(g.size()), n4 = n * 4;

        static u32 a[30 * 8];
        u32 *prev = a, *curr = a + n4;
        std::iota(prev, prev + n4, 0);

        u32 r = n * n * 4;

        auto merge = [&r] [[gnu::always_inline]] (u32 & x, u32 & y)
        {
            r += x != y;
            x = y;
        };

        constexpr u8 left = 0, right = 1, top = 2, bot = 3;

        for (u32 gy = 0, row_offset = 0; gy != n; ++gy, row_offset += n4)
        {
            std::iota(curr, curr + n4, gy * 4);
            u32 prev_right = curr[right];
            for (u32 gx = 0; gx != n; ++gx)
            {
                char c = g[gy][gx];

                u32* t = curr + gx * 4;
                u32* t_above = prev + gx * 4;

                // connect with the top cluster
                merge(t[top], t_above[bot]);

                // connect with the left cluster
                merge(t[left], prev_right);

                switch (c)
                {
                case ' ':
                    merge(t[left], t[top]);
                    merge(t[left], t[bot]);
                    merge(t[bot], t[right]);
                    break;
                case '/':
                    merge(t[left], t[top]);
                    merge(t[bot], t[right]);
                    break;
                case '\\':
                    merge(t[left], t[bot]);
                    merge(t[top], t[right]);
                    break;
                }

                prev_right = t[right];
            }

            std::swap(prev, curr);
        }

        return r;
    }
};
