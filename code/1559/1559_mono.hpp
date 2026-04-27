#include <concepts>
#include <cstdint>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};



inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    bool containsCycle(const std::vector<std::vector<char>>& g) noexcept
    {
        static u32 parent[500 * 500];

        auto find = [] [[gnu::always_inline]] (u32 x) noexcept
        {
            return parent[parent[x]];
        };

        auto merge = [find] [[gnu::always_inline]] (u32 x, u32 y) noexcept
        {
            parent[find(y)] = find(x);
        };

        char left = g[0][0];
        for (u32 x = 1; char c : g[0] | std::views::drop(1))
        {
            parent[x] = iif(c == left, parent[x - 1], x);
            left = c;
            ++x;
        }

        u32 ti = 0, ci = cast<u32>(g[0].size()), li = ci - 1;

        for (auto [prev_row, curr_row] : g | std::views::adjacent<2>)
        {
            left = 0;
            for (auto [top, curr] : std::views::zip(prev_row, curr_row))
            {
                parent[ci] = ci;
                if (left == curr)
                {
                    merge(li, ci);
                }

                if (top == curr)
                {
                    if (find(ti) == find(ci)) return true;
                    merge(ti, ci);
                }

                left = curr, ++ti, ++ci, ++li;
            }
        }

        return false;
    }
};
