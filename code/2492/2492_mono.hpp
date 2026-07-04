#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>


#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::min(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) noexcept -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

class Solution
{
public:
    using u16 = uint16_t;
    using u32 = uint32_t;

    inline static u16 min_road[100'001];
    inline static u32 parent[100'001];
    inline static u32 size[100'001];

    [[nodiscard, gnu::always_inline]] static u32 find(u32 x) noexcept
    {
        while (parent[x] != x)
        {
            auto& p = parent[x];
            x = p = parent[p];
        }
        return x;
    }

    u32 minScore(const u32 n, const std::vector<std::vector<int>>& roads)
        const noexcept
    {
        std::fill_n(min_road, n + 1, 0xFFFF);
        std::fill_n(size, n + 1, 1u);
        std::iota(parent, parent + n + 1, 0u);

        for (auto& road :
             reinterpret_cast<const std::vector<std::vector<u32>>&>(roads))
        {
            u32 x = find(road[0]), y = find(road[1]);

            if (x != y)
            {
                if (size[x] < size[y]) std::swap(x, y);
                parent[y] = x;
                size[x] += size[y];
                upd_min(min_road[x], min_road[y]);
            }
            upd_min(min_road[x], road[2] & 0xFFFF);
        }

        return min_road[find(1)];
    }
};
