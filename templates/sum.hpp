#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>

inline static constexpr auto sum =
    []<typename Range,
       typename T = std::ranges::range_value_t<Range>> [[gnu::always_inline]] (
        Range&& range,
        T&& init = {}) noexcept
{
    return std::ranges::fold_left(
        std::forward<Range>(range),
        std::forward<T>(init),
        std::plus<>{});
};
