#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>

#include "integral_aliases.hpp"

// https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/

template <auto value>
inline static constexpr auto kIntConst =
    std::integral_constant<decltype(value), value>{};

class Solution
{
public:
    inline static constexpr auto same =
        [] [[nodiscard, gnu::hot, gnu::always_inline]] (
            const std::vector<std::vector<int>>& m1,
            const std::vector<std::vector<int>>& m2,
            auto o) noexcept
    {
        u8 n = m1.size() & 0xFF, ci = 0, t = n - 1, gi = n - 1;
        if (n == 1) return m1 == m2;
        while (ci != n / 2)
        {
            for (u8 i = 0; i != t; ++i)
            {
                u8 y[]{
                    ci,
                    static_cast<u8>(ci + i),
                    gi,
                    static_cast<u8>(gi - i),
                };

                int v1[]{
                    m1[y[0]][y[1]],
                    m1[y[1]][y[2]],
                    m1[y[2]][y[3]],
                    m1[y[3]][y[0]],
                };

                int v2[]{
                    m2[y[(0 + o) & 3]][y[(1 + o) & 3]],
                    m2[y[(1 + o) & 3]][y[(2 + o) & 3]],
                    m2[y[(2 + o) & 3]][y[(3 + o) & 3]],
                    m2[y[(3 + o) & 3]][y[(0 + o) & 3]],
                };

                if (!std::ranges::equal(v1, v2))
                {
                    return false;
                }
            }
            ++ci, --gi, t -= 2;
        }
        return true;
    };

    [[nodiscard]] constexpr bool findRotation(
        const std::vector<std::vector<int>>& m1,
        const std::vector<std::vector<int>>& m2) const noexcept
    {
        auto f = std::bind(same, m1, m2, std::placeholders::_1);
        return f(kIntConst<0>) || f(kIntConst<1>) || f(kIntConst<2>) ||
               f(kIntConst<3>);
    }
};
