#include <bit>
#include <ranges>
#include <utility>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To>
inline static constexpr auto cast = []<typename From>(From&& v) INLINE_LAMBDA
{
    return static_cast<To>(std::forward<From>(v));
};

template <typename To>
inline static constexpr auto cast_view = std::views::transform(cast<To>);

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> countBits(
        unsigned n) noexcept
    {
        namespace stdv = std::views;
        return std::ranges::to<std::vector>(
            stdv::iota(0u, n + 1) | stdv::transform(std::popcount<unsigned>) |
            cast_view<int>);
    }
};
