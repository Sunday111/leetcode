#include <ranges>
#include <vector>


// https://leetcode.com/problems/construct-product-matrix/

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard, gnu::always_inline]] static constexpr u32 mul(
        uint64_t a,
        u32 b) noexcept
    {
        return (a * b) % 12345;
    }

    [[nodiscard]] auto constructProductMatrix(
        std::vector<std::vector<int>>& orig) noexcept
    {
        static u32 p[100'001];
        auto& g = reinterpret_cast<std::vector<std::vector<u32>>&>(orig);

        u32 i = 0;
        for (u32 t{1}; auto x : g | std::views::join)
        {
            p[i++] = std::exchange(t, mul(t, x));
        }

        for (u32 t{1}; auto& x : g | std::views::join | std::views::reverse)
        {
            x = mul(p[--i], std::exchange(t, mul(t, x)));
        }

        return std::move(orig);
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
